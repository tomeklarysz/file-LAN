#include <WinSock2.h>
#include <string>
#include <sstream>
#include "cleanup_socket.h"
#include "list_files.h"
#include "serve_file.h"
#define DEFAULT_BUFLEN 512

void handle_client(int client_socket);