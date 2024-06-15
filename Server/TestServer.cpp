#include"TestServer.h"

HDE::TestServer::TestServer() : SimpleServer(AF_INET,SOCK_STREAM,0,8080,INADDR_ANY,10) {
    launch();
}
void HDE::TestServer::AcceptConnection() {
    struct sockaddr_in address=getSocket()->getAddress();
    int addrlen=sizeof(address);
    newsocket=accept(getSocket()->getServer(),(struct sockaddr *)&address,(socklen_t*)&addrlen);
}

void HDE::TestServer::handleConnection() {
    read(newsocket,buffer,300000);
    std::cout<<buffer<<std::endl;

            printf("\n buffer message: %s \n ", buffer);
            char *parse_string_method = parse_method(buffer, " ");  //Try to get the path which the client ask for
            printf("Client method: %s\n", parse_string_method);

            //char httpHeader1[800021] = "HTTP/1.1 200 OK\r\n\n";

            char *parse_string = parse(buffer, " ");  //Try to get the path which the client ask for
            printf("Client ask for path: %s\n", parse_string);
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

char* HDE::TestServer::parse(char line[],const char symbol[]) {
    char *copy = (char *)malloc(strlen(line) + 1);
    strcpy(copy, line);
    
    char *message;
    char * token = strtok(copy, symbol);
    int current = 0;

    while( token != NULL ) {
      
      token = strtok(NULL, " ");
      if(current == 0){
          message = token;
          if(message == NULL){
              message = "";
          }
          return message;
      }
      current = current + 1;
   }
   free(token);
   free(copy);
   return message;
}

char* HDE::TestServer::parse_method(char line[], const char symbol[])
{
    char *copy = (char *)malloc(strlen(line) + 1);
    strcpy(copy, line);
        
    char *message;
    char * token = strtok(copy, symbol);
    int current = 0;

    while( token != NULL ) {
      
      //token = strtok(NULL, " ");
      if(current == 0){
          message = token;
          if(message == NULL){
              message = "";
          }
          return message;
      }
      current = current + 1;
   }
   free(copy);
   free(token);
   return message;
}
