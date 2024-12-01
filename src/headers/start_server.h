#include <iostream>
#include "cleanup_socket.h"
#include "handle_client.h"
#include <thread>

// for now only windows
#include <WinSock2.h>
#include <WS2tcpip.h>
 #pragma comment (lib, "Ws2_32.lib")
// -l ws2_32.lib

#define PORT "5000"

void start_server();