#include <iostream>
#include "headers/start_server.h"
#include "headers/cleanup_socket.h"
#include <thread>

// for now only windows
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
// -l ws_32.lib


void start_server() {
	
	WSADATA wsa_data;
	int result;

	SOCKET server_socket = INVALID_SOCKET;
	SOCKET client_socket = INVALID_SOCKET;
	
	struct addrinfo hints, *res, *p;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	// initialize socket
	result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		printf("WSAStartup failed with error: %d\n", result);
		WSACleanup();
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &res);

	for (p = res; p != NULL; p = p->ai_next) {

		if (server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol) < 0) {
			std::cerr << "Failed to create socket\n";
			continue;
		}

		if (bind(server_socket, p->ai_addr, p->ai_addrlen) < 0) {
			std::cerr << "Failed to bind socket\n";
			cleanup_socket(server_socket);
			continue;
		}
		
		if (listen(server_socket, 5) < 0) {
			std::cerr << "Failed to listen on socket\n";
			cleanup_socket(server_socket);
			continue;
		}

		std::cout << "Server listening on port " << PORT << "\n";

		break;
	}

	std::cout << "Server: waiting for connections...\n";

	while (true) {
		
		client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
		
		// if (client_socket >= 0) {
		// 	std::thread()
		// }
	}

	cleanup_socket(server_socket);
}