#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void handle_request(beast::string_view doc_root, http::request<http::string_body>&& req, http::response<http::string_body>&& res) {
    res.version(req.version());
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "Hello, World!";
    res.prepare_payload();
}

void session(tcp::socket socket) {
    bool close = false;
    beast::error_code ec;
    beast::flat_buffer buffer;

    http::request<http::string_body> req;
    http::read(socket, buffer, req, ec);

    http::response<http::string_body> res{http::status::ok, req.version()};
    handle_request(".", std::move(req), std::move(res));

    http::write(socket, res, ec);
    socket.shutdown(tcp::socket::shutdown_send, ec);
}

int main() {
    try {
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = 8080;

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{std::bind(&session, std::move(socket))}.detach();
        }
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
