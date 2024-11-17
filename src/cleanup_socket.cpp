#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif

void cleanup_socket(int socket_fd) {
#ifdef _WIN32
    closesocket(socket_fd);
    WSACleanup();
#else
    close(socket_fd);
#endif
}