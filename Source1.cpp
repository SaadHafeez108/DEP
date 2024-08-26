#include <fstream>
#include <sstream>

void handle_client(tcp::socket socket) {
    try {
        char data[1024];
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(data), error);

        if (error == boost::asio::error::eof) {
            return; // Connection closed cleanly by peer.
        }
        else if (error) {
            throw boost::system::system_error(error); // Some other error.
        }

        std::istringstream request_stream(std::string(data, length));
        std::string request_method;
        std::string request_path;

        request_stream >> request_method >> request_path;

        if (request_method == "GET") {
            std::string file_path = "." + request_path;
            std::ifstream file(file_path);
            if (file) {
                std::ostringstream ss;
                ss << file.rdbuf();
                std::string content = ss.str();

                std::ostringstream response_stream;
                response_stream << "HTTP/1.1 200 OK\r\n";
                response_stream << "Content-Length: " << content.size() << "\r\n";
                response_stream << "Content-Type: text/html\r\n";
                response_stream << "\r\n";
                response_stream << content;

                boost::asio::write(socket, boost::asio::buffer(response_stream.str()));
            }
            else {
                std::string not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
                boost::asio::write(socket, boost::asio::buffer(not_found));
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}
