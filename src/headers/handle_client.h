#include <WinSock2.h>
#include <string>
#include <sstream>
#include "headers/cleanup_socket.h"
#include "headers/list_files.h"
#include "headers/serve_file.h"
#define DEFAULT_BUFLEN 512

void handle_client(int client_socket);