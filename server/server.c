#include <winsock2.h>
#include <stdio.h>
#include "polynomial.h"

#pragma comment(lib,"ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char buffer[1024];

    double coeffs[] = {1, -2, 3}; // приклад: x^2 - 2x + 3
    Polynomial* poly = create_polynomial(2, coeffs);

    WSAStartup(MAKEWORD(2,2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 3);

    printf("Server listening...\n");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr*)&client, &c);

    while((recv_size = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[recv_size] = '\0';

        if(buffer[0] == 'x') { // запит значення
            double x = atof(buffer+2);
            double result = evaluate_polynomial(poly, x);
            sprintf(buffer, "%lf", result);
        } else if(buffer[0] == 'd') { // запит порядку
            sprintf(buffer, "%d", get_degree(poly));
        } else if(buffer[0] == 'c') { // запит коефіцієнтів
            char tmp[256] = "";
            for(int i=0; i<=poly->degree; i++) {
                char num[32];
                sprintf(num, "%lf ", poly->coeffs[i]);
                strcat(tmp, num);
            }
            strcpy(buffer, tmp);
        }

        send(new_socket, buffer, strlen(buffer), 0);
    }

    free_polynomial(poly);
    closesocket(s);
    WSACleanup();
    return 0;
}
