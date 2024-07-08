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
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error on fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        // Child process
        char buffer[30000] = {0};
        ssize_t valread = read(newsocket, buffer, sizeof(buffer) - 1);
        if (valread < 0) {
            perror("Error reading from socket");
            exit(EXIT_FAILURE);
        }

        printf("\n buffer message: %s \n", buffer);
        char *parse_string_method = parse_method(buffer, " ");
        printf("Client method: %s\n", parse_string_method);

        char *parse_string = parse(buffer, " ");
        printf("Client ask for path: %s\n", parse_string);

        char *copy = strdup(parse_string);
        if (!copy) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        char *parse_ext = parse(copy, ".");

        char *copy_head = (char *)malloc(strlen(http_header) + 200);
        if (!copy_head) {
            perror("Memory allocation failed");
            free(copy);
            exit(EXIT_FAILURE);
        }
        strcpy(copy_head, http_header);

        if (strncmp(parse_string_method, "GET", 3) == 0) {
            // Handle GET requests
            // ... (rest of the GET handling code)
            if(strlen(parse_string) <= 1){
                    //case that the parse_string = "/"  --> Send index.html file
                    //write(new_socket , httpHeader , strlen(httpHeader));
                    char path_head[500] = ".";
                    strcat(path_head, "/index.html");
                    strcat(copy_head, "Content-Type: text/html\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
               else if ((parse_ext[0] == 'j' && parse_ext[1] == 'p' && parse_ext[2] == 'g') || (parse_ext[0] == 'J' && parse_ext[1] == 'P' && parse_ext[2] == 'G'))
                {
                    //send image to client
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: image/jpeg\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[0] == 'i' && parse_ext[1] == 'c' && parse_ext[2] == 'o')
                {
                    //https://www.cisco.com/c/en/us/support/docs/security/web-security-appliance/117995-qna-wsa-00.html
                    char path_head[500] = ".";
                    strcat(path_head, "/img/favicon.png");
                    strcat(copy_head, "Content-Type: image/vnd.microsoft.icon\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[0] == 't' && parse_ext[1] == 't' && parse_ext[2] == 'f')
                {
                    //font type, to display icon from FontAwesome
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: font/ttf\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[strlen(parse_ext)-2] == 'j' && parse_ext[strlen(parse_ext)-1] == 's')
                {
                    //javascript
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: text/javascript\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[strlen(parse_ext)-3] == 'c' && parse_ext[strlen(parse_ext)-2] == 's' && parse_ext[strlen(parse_ext)-1] == 's')
                {
                    //css
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: text/css\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[0] == 'w' && parse_ext[1] == 'o' && parse_ext[2] == 'f')
                {
                    //Web Open Font Format woff and woff2
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: font/woff\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[0] == 'm' && parse_ext[1] == '3' && parse_ext[2] == 'u' && parse_ext[3] == '8')
                {
                    //Web Open m3u8
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: application/vnd.apple.mpegurl\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else if (parse_ext[0] == 't' && parse_ext[1] == 's')
                {
                    //Web Open ts
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: video/mp2t\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                }
                else{
                    //send other file 
                    char path_head[500] = ".";
                    strcat(path_head, parse_string);
                    strcat(copy_head, "Content-Type: text/plain\r\n\r\n");
                    send_message(newsocket, path_head, copy_head);
                    printf("Else: %s \n", parse_string);        
                }
                printf("\n------------------Server sent----------------------------------------------------\n");
        } else if (strncmp(parse_string_method, "POST", 4) == 0) {
            // Handle POST requests
            char *find_string = find_token(buffer, "\r\n", "action");
            strcat(copy_head, "Content-Type: text/plain\r\n\r\n");
            strcat(copy_head, "User Action: ");
            printf("find string: %s \n", find_string);
            strcat(copy_head, find_string);
            write(newsocket, copy_head, strlen(copy_head));
        }

        close(newsocket);
        free(copy);
        free(copy_head);
        exit(EXIT_SUCCESS);  // Exit child process
    } else {
        // Parent process
        printf("Parent created child with pid: %d\n", pid);
        close(newsocket);
    }
}

void HDE::TestServer::respondConnection() {
    close(newsocket);
    return;
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

    return 0;
}

char* HDE::TestServer::find_token(char line[], const char symbol[], const char match[])
{
    char *copy = (char *)malloc(strlen(line) + 1);
    strcpy(copy, line);
        
    char *message;
    char * token = strtok(copy, symbol);

    while( token != NULL ) {
      
      //printf("--Token: %s \n", token);
      
      if(strlen(match) <= strlen(token))
      {
          int match_char = 0;
          for(int i = 0; i < strlen(match); i++)
          {
              if(token[i] == match[i])
              {
                  match_char++;
              }
          }
          if(match_char == strlen(match)){
            message = token;
            return message;
          }
      }      
      token = strtok(NULL, symbol);
   }
   free(copy);
   free(token);
   message = "";
   return message;
}



