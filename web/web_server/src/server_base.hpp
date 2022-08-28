//
// server_base.hpp
// web_server
// created by changkun at shiyanlou.com
//

#ifndef SERVER_BASE_HPP
#define	SERVER_BASE_HPP

#include <boost/asio.hpp>

#include <regex>
#include <unordered_map>
#include <thread>

namespace ShiyanlouWeb {
    struct Request {
        // 请求方法, POST, GET; 请求路径; HTTP 版本
        std::string method, path, http_version;
        // 对 content 使用智能指针进行引用计数
        std::shared_ptr<std::istream> content;
        // 哈希容器, key-value 字典
        std::unordered_map<std::string, std::string> header;
        // 用正则表达式处理路径匹配
        std::smatch path_match;
    };

    // 使用 typedef 简化资源类型的表示方式
    typedef std::map<std::string, std::unordered_map<std::string,
    std::function<void(std::ostream&, Request&)>>> resource_type;

    // socket_type 为 HTTP or HTTPS
    template <typename socket_type>
    class ServerBase {
    public:
        resource_type resource;
        resource_type default_resource;

        // 构造服务器, 初始化端口, 默认使用一个线程
        ServerBase(unsigned short port, size_t num_threads = 1) :
            endpoint(boost::asio::ip::tcp::v4(), port),
            acceptor(m_io_service, endpoint),
            num_threads(num_threads) {}

        void start() {
            // 默认资源放在 vector 的末尾, 用作应答方法
            for(auto it = resource.begin(); it != resource.end(); it++) {
                all_resources.push_back(it);
            }
            for(auto it = default_resource.begin(); it != default_resource.end(); it++) {
                all_resources.push_back(it);
            }

            // 调用 socket 的连接方式
            accept();

            // 如果 num_threads>1, 那么 m_io_service.run()
            // 将运行 (num_threads-1) 线程成为线程池
            for(size_t c = 1;c < num_threads; c++) {
                threads.emplace_back([this](){
                    m_io_service.run();
                });
            }

            // 主线程
            m_io_service.run();

            // 等待其他线程，如果有的话, 就等待这些线程的结束
            for(auto& t: threads)
                t.join();
        }
    protected:
        // asio 库中的 io_service 是调度器，所有的异步 IO 事件都要通过它来分发处理
        // 换句话说, 需要 IO 的对象的构造函数，都需要传入一个 io_service 对象
        boost::asio::io_service m_io_service;
        // IP 地址、端口号、协议版本构成一个 endpoint，并通过这个 endpoint 在服务端生成
        // tcp::acceptor 对象，并在指定端口上等待连接
        boost::asio::ip::tcp::endpoint endpoint;
        // 所以，一个 acceptor 对象的构造都需要 io_service 和 endpoint 两个参数
        boost::asio::ip::tcp::acceptor acceptor;

        // 服务器线程
        size_t num_threads;
        std::vector<std::thread> threads;

        // 所有的资源及默认资源都会在 vector 尾部添加, 并在 start() 中创建
        std::vector<resource_type::iterator> all_resources;

        // 需要不同类型的服务器实现这个方法
        virtual void accept() {}

        // 处理请求和应答
        void process_request_and_respond(std::shared_ptr<socket_type> socket) const {
            // 为 async_read_untile() 创建新的读缓存
            // Shared_ptr 用于传递临时对象给匿名函数
            // 会被推导为 std::shared_ptr<boost::asio::streambuf>
            auto read_buffer = std::make_shared<boost::asio::streambuf>();

            boost::asio::async_read_until(*socket, *read_buffer, "\r\n\r\n",
            [this, socket, read_buffer](const boost::system::error_code& ec, size_t bytes_transferred) {
                if(!ec) {
                    // 注意：read_buffer->size() 的大小并一定和 bytes_transferred 相等， Boost 的文档中指出：
                    // 在 async_read_until 操作成功后,  streambuf 在界定符之外可能包含一些额外的的数据
                    // 所以较好的做法是直接从流中提取并解析当前 read_buffer 左边的报头, 再拼接 async_read 后面的内容
                    size_t total = read_buffer->size();

                    // 转换到 istream 来提取 string-lines
                    std::istream stream(read_buffer.get());

                    // 被推导为 std::shared_ptr<Request> 类型
                    auto request = std::make_shared<Request>();
                    *request = parse_request(stream);

                    size_t num_additional_bytes = total-bytes_transferred;

                    // 如果满足，同样读取
                    if(request->header.count("Content-Length")>0) {
                        boost::asio::async_read(*socket, *read_buffer,
                        boost::asio::transfer_exactly(stoull(request->header["Content-Length"]) - num_additional_bytes),
                        [this, socket, read_buffer, request](const boost::system::error_code& ec, size_t bytes_transferred) {
                            if(!ec) {
                                // 将指针作为 istream 对象存储到 read_buffer 中
                                request->content = std::shared_ptr<std::istream>(new std::istream(read_buffer.get()));
                                respond(socket, request);
                            }
                        });
                    } else {
                        respond(socket, request);
                    }
                }
            });
        }

        // 解析请求
        Request parse_request(std::istream& stream) const {
            Request request;

            std::regex e("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");

            std::smatch sub_match;

            //从第一行中解析请求方法、路径和 HTTP 版本
            std::string line;
            getline(stream, line);
            line.pop_back();
            if(std::regex_match(line, sub_match, e)) {
                request.method       = sub_match[1];
                request.path         = sub_match[2];
                request.http_version = sub_match[3];

                bool matched;
                e="^([^:]*): ?(.*)$";
                // 解析头部的其他信息
                do {
                    getline(stream, line);
                    line.pop_back();
                    matched=std::regex_match(line, sub_match, e);
                    if(matched) {
                        request.header[sub_match[1]] = sub_match[2];
                    }

                } while(matched==true);
            }
            return request;
        }

        // 应答
        void respond(std::shared_ptr<socket_type> socket, std::shared_ptr<Request> request) const {
            // 对请求路径和方法进行匹配查找，并生成响应
            for(auto res_it: all_resources) {
                std::regex e(res_it->first);
                std::smatch sm_res;
                if(std::regex_match(request->path, sm_res, e)) {
                    if(res_it->second.count(request->method)>0) {
                        request->path_match = move(sm_res);

                        // 会被推导为 std::shared_ptr<boost::asio::streambuf>
                        auto write_buffer = std::make_shared<boost::asio::streambuf>();
                        std::ostream response(write_buffer.get());
                        res_it->second[request->method](response, *request);

                        // 在 lambda 中捕获 write_buffer 使其不会再 async_write 完成前被销毁
                        boost::asio::async_write(*socket, *write_buffer,
                        [this, socket, request, write_buffer](const boost::system::error_code& ec, size_t bytes_transferred) {
                            //HTTP 持久连接(HTTP 1.1):
                            if(!ec && stof(request->http_version)>1.05)
                                process_request_and_respond(socket);
                        });
                        return;
                    }
                }
            }
        }

    };

    template<typename socket_type>
    class Server : public ServerBase<socket_type> {};
}
#endif	/* SERVER_BASE_HPP */
