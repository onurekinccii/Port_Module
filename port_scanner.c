// port_scanner.c
#include <stdint.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

__declspec(dllexport) int32_t is_port_open(const char* ip, int32_t port) {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    int result;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 0;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return 0;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    result = connect(sock, (struct sockaddr*)&server, sizeof(server));

    closesocket(sock);
    WSACleanup();

    return (result == 0);
}
