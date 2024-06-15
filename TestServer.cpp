#include"TestServer.h"

HDE::TestServer::TestServer() : SimpleServer(AF_INET,SOCK_STREAM,0,8080,INADDR_ANY,10) {
    launch();
}
void HDE::TestServer::AcceptConnection() {
    struct sockaddr_in address=getSocket()->getAddress();
    int addrlen=sizeof(address);
    newsocket=accept(getSocket()->getServer(),(struct sockaddr *)&address,(socklen_t*)&addrlen);
    read(newsocket,buffer,300000);
}

void HDE::TestServer::handleConnection() {
    std::cout<<buffer<<std::endl;
}

void HDE::TestServer::respondConnection() {
    char* hello="Hello from server";
    send(newsocket,hello,strlen(hello),0);
    close(newsocket);
}

void HDE::TestServer::launch() {
    while(1) {
        printf("======waiting for client======\n");
        AcceptConnection();
        handleConnection();
        respondConnection();
        printf("======Data sent to client======\n");
    }
}