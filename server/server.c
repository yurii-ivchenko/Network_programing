#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "polynomial.h"

#pragma comment(lib,"ws2_32.lib")

Polynomial* poly;
CRITICAL_SECTION cs; 

DWORD WINAPI ClientHandler(LPVOID socket_desc) {
    SOCKET client_sock = *(SOCKET*)socket_desc;
    char buffer[1024];
    int recv_size;

    while((recv_size = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[recv_size] = '\0';

        EnterCriticalSection(&cs); 

        if(buffer[0] == 'x') {
            double x = atof(buffer+2);
            double result = evaluate_polynomial(poly, x);
            sprintf(buffer, "%lf", result);
        } else if(buffer[0] == 'd') {
            sprintf(buffer, "%d", get_degree(poly));
        } else if(buffer[0] == 'c') {
            char tmp[256] = "";
            for(int i=0; i<=poly->degree; i++) {
                char num[32];
                sprintf(num, "%lf ", poly->coeffs[i]);
                strcat(tmp, num);
            }
            strcpy(buffer, tmp);
        }

        LeaveCriticalSection(&cs);

        send(client_sock, buffer, strlen(buffer), 0);
    }

    closesocket(client_sock);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;

    double coeffs[] = {1, -2, 3}; // приклад: x^2 - 2x + 3
    poly = create_polynomial(2, coeffs);

    InitializeCriticalSection(&cs);

    WSAStartup(MAKEWORD(2,2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 3);

    printf("Server listening...\n");
    c = sizeof(struct sockaddr_in);

    while((new_socket = accept(s, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
        printf("Client connected!\n");
        HANDLE thread = CreateThread(NULL, 0, ClientHandler, (LPVOID)&new_socket, 0, NULL);
        if(thread == NULL) {
            printf("Thread creation failed\n");
        } else {
            CloseHandle(thread);
        }
    }

    DeleteCriticalSection(&cs);
    free_polynomial(poly);
    closesocket(s);
    WSACleanup();
    return 0;
}
