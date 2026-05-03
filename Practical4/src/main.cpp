#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>

struct ICMPHeader {
    unsigned char type;
    unsigned char code;
    unsigned short checksum;
    unsigned short id;
    unsigned short seq;
};

unsigned short checksum(unsigned short* buf, int size) {
    unsigned long sum = 0;
    while (size > 1) {
        sum += *buf++;
        size -= 2;
    }
    if (size) sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

void sendPing(const std::string& ip) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Raw socket creation failed" << std::endl;
        WSACleanup();
        return;
    }

    sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(ip.c_str());

    for (int i = 1; i <= 4; i++) {
        ICMPHeader icmp;
        icmp.type = 8; // Echo Request
        icmp.code = 0;
        icmp.id = (unsigned short)GetCurrentProcessId();
        icmp.seq = i;
        icmp.checksum = 0;
        icmp.checksum = checksum((unsigned short*)&icmp, sizeof(icmp));

        auto start = std::chrono::high_resolution_clock::now();

        int result = sendto(sock, (char*)&icmp, sizeof(icmp), 0,
            (sockaddr*)&dest, sizeof(dest));
        if (result == SOCKET_ERROR) {
            std::cerr << "Send failed" << std::endl;
            continue;
        }

        char buffer[1024];
        int len = sizeof(dest);
        int bytes = recvfrom(sock, buffer, sizeof(buffer), 0,
            (sockaddr*)&dest, &len);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (bytes > 0) {
            std::cout << "Reply from " << ip
                << ": bytes=" << bytes
                << " time=" << duration << "ms"
                << " seq=" << i << std::endl;
        }
        else {
            std::cout << "Request timed out (seq=" << i << ")" << std::endl;
        }

        Sleep(1000); 
    }

    closesocket(sock);
    WSACleanup();
}

int main() {
    std::string ip;
    std::cout << "Enter IP address to ping: ";
    std::getline(std::cin, ip);

    sendPing(ip);

    system("pause"); 
    return 0;
}
