#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char buffer[1024];

    WSAStartup(MAKEWORD(2,2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    connect(s, (struct sockaddr*)&server, sizeof(server));

    // приклад: запит значення при x=2
    strcpy(buffer, "x 2");
    send(s, buffer, strlen(buffer), 0);
    recv(s, buffer, sizeof(buffer), 0);
    printf("Result: %s\n", buffer);

    // запит порядку
    strcpy(buffer, "d");
    send(s, buffer, strlen(buffer), 0);
    recv(s, buffer, sizeof(buffer), 0);
    printf("Degree: %s\n", buffer);

    // запит коефіцієнтів
    strcpy(buffer, "c");
    send(s, buffer, strlen(buffer), 0);
    recv(s, buffer, sizeof(buffer), 0);
    printf("Coeffs: %s\n", buffer);

    closesocket(s);
    WSACleanup();
    return 0;
}
