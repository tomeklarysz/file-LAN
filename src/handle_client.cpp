#include "headers/handle_client.h"
#include <string>
#include <stdexcept>
#include <sstream>

std::string url_decode(const std::string& encoded) {
    std::string decoded;
    decoded.reserve(encoded.length());

    for (size_t i = 0; i < encoded.length(); ++i) {
        if (encoded[i] == '%' && i + 2 < encoded.length()) {
            // Get the two hex digits following %
            std::string hex = encoded.substr(i + 1, 2);
            try {
                int value = std::stoi(hex, nullptr, 16);
                decoded += static_cast<char>(value);
                i += 2;
            } catch (const std::exception&) {
                // If invalid hex, just add the % as is
                decoded += '%';
            }
        }
        else if (encoded[i] == '+') {
            decoded += ' ';  // Convert + to space
        }
        else {
            decoded += encoded[i];
        }
    }

    return decoded;
}

void send_http_response(int client_socket, int status_code, const std::string& content_type, const std::string& content) {
    std::string status_text = status_code == 200 ? "OK" : (status_code == 404 ? "Not Found" : "Bad Request");
    
    std::ostringstream response;
    response << "HTTP/1.1 " << status_code << " " << status_text << "\r\n"
             << "Content-Type: " << content_type << "\r\n"
             << "Connection: close\r\n"
             << "Content-Length: " << content.size() << "\r\n"
             << "\r\n"
             << content;
             
    send(client_socket, response.str().c_str(), response.str().size(), 0);
}

void handle_client(int client_socket) {
    char buffer[DEFAULT_BUFLEN] = {0};
    int bytes_received = recv(client_socket, buffer, DEFAULT_BUFLEN - 1, 0);
    if (bytes_received <= 0) {
        cleanup_socket(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    std::string request(buffer);
  
    // parse HTTP request
    std::istringstream request_stream(request);
    std::string method, path, protocol;
    request_stream >> method >> path >> protocol;

    if (method == "GET") {
        if (path == "/files") {
            send_http_response(client_socket, 200, "text/plain", list_files());
        } else if (path.rfind("/files/download/", 0) == 0) {
            std::string filename = url_decode(path.substr(15));
            
            if (!serve_file(filename, client_socket)) {
                send_http_response(client_socket, 404, "text/plain", "File not found: " + filename);
                cleanup_socket(client_socket);
            }
        } else {
            send_http_response(client_socket, 404, "text/plain", "Unknown endpoint");
            cleanup_socket(client_socket);
        }
    } else {
        send_http_response(client_socket, 400, "text/plain", "Unsupported method");
        cleanup_socket(client_socket);
    }

}