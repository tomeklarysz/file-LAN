#include "headers/handle_client.h"
#

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
  std::string method, path;
  request_stream >> method >> path;

  if (method == "GET") {
    if (path == "/files") {
      std::string response = list_files();
      send(client_socket, response.c_str(), response.size(), 0);
    } else if (path.rfind("/download/", 0) == 0) {
      std::string filename = path.substr(10);
      serve_file(filename, client_socket);
    } else {
      std::string response = "HTTP/1.1 404 Not Found\r\n\r\nUnknown endpoint\n";
      send(client_socket, response.c_str(), response.size(), 0);
    }
  } else {
    std::string response = "HTTP/1.1 404 Bad Request\r\n\r\nUnsupported method\n";
    send(client_socket, response.c_str(), response.size(), 0);
  }

  cleanup_socket(client_socket);
}