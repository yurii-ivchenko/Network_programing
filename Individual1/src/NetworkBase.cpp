#include "NetworkBase.h"

NetworkBase::NetworkBase() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    m_socket = INVALID_SOCKET;
}

NetworkBase::~NetworkBase() {
    Close();
    WSACleanup();
}

void NetworkBase::Close() {
    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}

bool NetworkBase::SendMessage(SOCKET target, const std::string& msg) {
    int res = send(target, msg.c_str(), (int)msg.length(), 0);
    return res != SOCKET_ERROR;
}

std::string NetworkBase::ReceiveMessage(SOCKET target) {
    char buffer[1024] = { 0 };
    int res = recv(target, buffer, 1024, 0);
    if (res > 0) return std::string(buffer, res);
    return "";
}