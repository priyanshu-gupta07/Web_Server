#include"TestServer.h"
#include <sstream>
#include <string.h>
#include <ostream>
#include <iostream>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>

char http_header[25] = "HTTP/1.1 200 Ok\r\n";

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

            // std::ostringstream oss;
            // oss << "HTTP/1.1 200 OK\r\n\n";
            // oss << "Cache-Control: no-cache, private\r\n";
            // oss << "Content-Type: text/plain\r\n";
            // oss << "Content-Length: 12\r\n";
            // oss << "\r\n";
            // oss << "Hello World!";

            // std::string response = oss.str();
            // int size=response.size()+1;
            // send(newsocket,response.c_str(),size,0);

            char *copy = (char *)malloc(strlen(parse_string) + 1);
            strcpy(copy, parse_string);
            char *parse_ext = parse(copy, ".");  // get the file extension such as JPG, jpg

            char *copy_head = (char *)malloc(strlen(http_header) +200);
            strcpy(copy_head, http_header);

            if(parse_string_method[0] == 'G' && parse_string_method[1] == 'E' && parse_string_method[2] == 'T'){
                //https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types
                if(strlen(parse_string) <= 1){
                    //case that the parse_string = "/"  --> Send index.html file
                    //write(new_socket , httpHeader , strlen(httpHeader));
                    char path_head[500] = ".";
                    strcat(path_head, "/Server/HTML/index.html");
                    strcat(copy_head, "Content-Type: text/html\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
            }

}

void HDE::TestServer::respondConnection() {
    // char* hello="Hello from server";
    // send(newsocket,hello,strlen(hello),0);
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

int HDE::TestServer::send_message(int fd, char image_path[], char head[]){
    /*
    char imageheader[] = 
    "HTTP/1.1 200 Ok\r\n"
    "Content-Type: image/jpeg\r\n\r\n";
    */
    struct stat stat_buf;  /* hold information about input file */

    write(fd, head, strlen(head));

    int fdimg = open(image_path, O_RDONLY);
    
    if(fdimg < 0){
        printf("Cannot Open file path : %s with error %d\n", image_path, fdimg); 
    }
     
    fstat(fdimg, &stat_buf);
    int img_total_size = stat_buf.st_size;
    int block_size = stat_buf.st_blksize;
    //printf("image block size: %d\n", stat_buf.st_blksize);  
    //printf("image total byte st_size: %d\n", stat_buf.st_size);
    if(fdimg >= 0){
        ssize_t sent_size;

        while(img_total_size > 0){
              int send_bytes = ((img_total_size < block_size) ? img_total_size : block_size);
              int done_bytes = sendfile(fd, fdimg, NULL, block_size);
              img_total_size = img_total_size - done_bytes;
        }
        if(sent_size >= 0){
            printf("send file: %s \n" , image_path);
        }
        close(fdimg);
    }
}
