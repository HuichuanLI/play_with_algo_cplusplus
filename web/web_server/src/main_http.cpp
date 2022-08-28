//
// main_http.cpp
// web_server
// created by changkun at shiyanlou.com
//


#include "server_http.hpp"
#include "handler.hpp"

using namespace ShiyanlouWeb;

int main() {
    // HTTP 服务运行在 12345 端口，并启用四个线程
    Server<HTTP> server(12345, 4);
    start_server<Server<HTTP>>(server);
    return 0;
}
