#include "headers/start_server.h"

void start_server() {
	
	WSADATA wsa_data;
	int result;

	int server_socket, client_socket;
	
	struct addrinfo hints, *res, *p;
	struct sockaddr_in client_addr {};
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

	getaddrinfo("0.0.0.0", PORT, &hints, &res);

	for (p = res; p != NULL; p = p->ai_next) {

		server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (server_socket < 0) {
			std::cerr << "Failed to create socket\n";
			return;
		}

		printf("socket: %d\n",server_socket);

		int opt = 1;
		if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt)) == -1) {
			perror("setsockopt");
			return;
		}

		if (bind(server_socket, p->ai_addr, p->ai_addrlen) < 0) {
			std::cerr << "Failed to bind socket\n";
			cleanup_socket(server_socket);
			return;
		}
		break;
	}

	if (p == NULL) {
		std::cerr << "Failed to bind to any address\n";
		return;
	}

	freeaddrinfo(res);

	if (listen(server_socket, 5) < 0) {
			std::cerr << "Failed to listen on socket\n";
			cleanup_socket(server_socket);
			return;
	}
	std::cout << "Server listening on port " << PORT << "\n";

	while (true) {
		
		client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
		
		if (client_socket >= 0) {
			std::thread(handle_client, client_socket).detach();
		}
	}

	cleanup_socket(server_socket);
}