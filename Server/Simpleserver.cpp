#include"Simpleserver.h"

HDE::SimpleServer::SimpleServer(int domain, int service, int type, int port, u_long interface,int backlog) {
    Socket = new ListeningSocket(domain, service, type, port, interface,backlog);
}

HDE::ListeningSocket* HDE::SimpleServer::getSocket() {
    return Socket;
}
        