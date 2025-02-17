#include <WinSock2.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
// #include "list_files.h"
#define DEFAULT_BUFLEN 512
bool serve_file(const std::string &filename, int client_socket);