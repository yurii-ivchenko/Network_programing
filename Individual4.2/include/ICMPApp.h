#pragma once
#include <winsock2.h>
#include <string>

class ICMPApp {
public:
    ICMPApp(const std::string& ip);
    ~ICMPApp();
    void sendEchoRequest();

private:
    SOCKET sock;
    sockaddr_in dest;
};
