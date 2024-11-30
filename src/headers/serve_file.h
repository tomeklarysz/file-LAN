#include <WinSock2.h>
#include <string>
#include <fstream>
#include <filesystem>
// #include "list_files.h"
#define DEFAULT_BUFLEN 512
std::string serve_file(const std::string &filename, int client_socket);