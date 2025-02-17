#include "headers/serve_file.h"

namespace fs = std::filesystem;
const std::string SHARED_DIR = "./shared_files";
bool serve_file(const std::string &filename, int client_socket) {
    std::string file_path = SHARED_DIR + "/" + filename;
    if (!fs::exists(file_path)) {
        return false;
    }

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Send HTTP headers
    std::ostringstream headers{};
    headers << "HTTP/1.1 200 OK\r\n"
            << "Content-Type: application/octet-stream\r\n"
            << "Content-Disposition: attachment; filename=\"" << filename << "\"\r\n"
            << "Content-Length: " << file_size << "\r\n"
            << "Connection: close\r\n"
            << "\r\n";
    
    // Send headers and check for errors
    ssize_t sent_bytes = send(client_socket, headers.str().c_str(), headers.str().size(), 0);
    if (sent_bytes <= 0) {
        file.close();
        return false;
    }

    // Send file content
    char buffer[DEFAULT_BUFLEN];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        sent_bytes = send(client_socket, buffer, file.gcount(), 0);
        if (sent_bytes <= 0) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}