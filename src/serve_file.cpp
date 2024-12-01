#include "headers/serve_file.h"

namespace fs = std::filesystem;
const std::string SHARED_DIR = "./shared_files";
std::string serve_file(const std::string &filename, int client_socket) {
    std::string file_path = SHARED_DIR + "/" + filename;
    if (!fs::exists(file_path)) {
        return "HTTP/1.1 404 Not Found\r\n\r\nFile not found\n";
    }

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return "HTTP/1.1 500 Internal Server Error\r\n\r\nUnable to open file\n";
    }

    // Send HTTP headers
    std::ostringstream headers{};
    headers << "HTTP/1.1 200 OK\r\nContent-Type: application/octet-stream\r\n\r\n";
    send(client_socket, headers.str().c_str(), headers.str().size(), 0);

    // Send file content
    char buffer[DEFAULT_BUFLEN];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        send(client_socket, buffer, file.gcount(), 0);
    }

    file.close();
    return "";
}