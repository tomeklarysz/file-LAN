#include "headers/list_files.h"


std::string list_files() {
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    for (const auto &entry : fs::directory_iterator(SHARED_DIR)) {
        if (entry.is_regular_file()) {
            response << entry.path().filename().string() << " (" << entry.file_size() << " bytes)\n";
        }
    }
    return response.str();
}