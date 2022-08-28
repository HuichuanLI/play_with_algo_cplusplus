//
// server_https.hpp
// web_server
// created by changkun at shiyanlou.com
//

#ifndef SERVER_HTTPS_HPP
#define	SERVER_HTTPS_HPP

#include "server_http.hpp"
#include <boost/asio/ssl.hpp>

namespace ShiyanlouWeb {

    // 定义 HTTPS 类型
    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> HTTPS;

    // 定义 HTTPS 服务, 模板类型为 HTTPS
    template<>
    class Server<HTTPS> : public ServerBase<HTTPS> {
    public:
        // 一个 HTTPS 的服务器比 HTTP 服务器多增加了两个参数，一个是证书文件，另一个是私钥文件
        Server(unsigned short port, size_t num_threads,
               const std::string& cert_file, const std::string& private_key_file) :
          ServerBase<HTTPS>::ServerBase(port, num_threads),
          context(boost::asio::ssl::context::sslv23) {
            // 使用证书文件
            context.use_certificate_chain_file(cert_file);
            // 使私钥文件, 相比之下需要多传入一个参数来指明文件的格式
            context.use_private_key_file(private_key_file, boost::asio::ssl::context::pem);
        }

    private:
        // 和 HTTP 服务器相比，需要多定义一个 ssl context 对象
        boost::asio::ssl::context context;

        // HTTPS 服务器和 HTTP 服务器相比
        // 其区别在于对 socket 对象的构造方式有所不同
        // HTTPS 会在 socket 这一步中对 IO 流进行加密
        // 因此实现的 accept() 方法需要对 socket 用 ssl context 初始化
        void accept() {
            // 为当前连接创建一个新的 socket
            // Shared_ptr 用于传递临时对象给匿名函数
            // socket 类型会被推导为: std::shared_ptr<HTTPS>
            auto socket = std::make_shared<HTTPS>(m_io_service, context);

            acceptor.async_accept(
                (*socket).lowest_layer(),
                [this, socket](const boost::system::error_code& ec) {
                    // 立即启动并接受一个新连接
                    accept();

                    // 处理错误
                    if(!ec) {
                        (*socket).async_handshake(boost::asio::ssl::stream_base::server,
                            [this, socket](const boost::system::error_code& ec) {
                            if(!ec) process_request_and_respond(socket);
                        });
                    }
            });
        }
    };
}

#endif	/* SERVER_HTTPS_HPP */
