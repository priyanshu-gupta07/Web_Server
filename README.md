# Simple Http Web Server in Linux using C/C++ from Scratch
Here we build a http web server from scratch without using any third party library. I'm refrerring this reading resource,[Medium link](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
.This is really helpful to get you started on this. 


# 1. Basic Knowledge <br />
In the internet world, there is always a server who can serve multiple clients. For example, Google, Netflix, Facebook... and so on are servers. People like us are client and we can use web browser (Chrome, Edge, Opera, Firefox....) to communicate with servers. <br />

You can make a web server at your home and use your own laptop to access the server through LAN which stands for Local Area Network (having a Wi-Fi router can create a LAN at your home). However, if your html file includes some resources in WAN (Wide Area Network), then you need to be able to access the internet for displaying your html correctly.

What you need is at least one PC or laptop (acts as server) running in Linux (
[Ubuntu](https://ubuntu.com/desktop)
or Debian) which should connect to the router. You can use cell phone as a client.  

# 2. Overview
We are going to implement code for a http server on Ubuntu Desktop.As for code editor I'm using <b>Visual Studio Code</b> 

## 2.1 System Requirement
<p align="center">
<table>
    <thead>
        <tr>
            <th align="center">Role</th>
            <th align="center">Requirement</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td align="center">Web Server</td>
            <td align="Left">Linux OS such as <b>Ubuntu</b> or <b>Debian</b>. <br />C\C++ development environment: <b>Visual Studio Code </b>or <b>Geany</b></td>
        </tr>
        <tr>
            <td align="center">Client</td>
            <td align="Left">Whatever OS (Windows, IOS, Android, Ubuntu) which is able to access web browser is good. You can use your cell phone as well.</td>
        </tr>
    </tbody>
</table>
</p>


## 3.1 Code Structure
We have Implemented the Socket Functionality in the Socket Folder where you can easily look at the modular implemantion of Socket functionality using the Traditional Classes and inheritance.
The server folder is here Responsible for running the Connection as well as Parsing the query coming from the Clients and sending the Desire Response.

## 3.2 Parse the Request from the Client
Let's take a look at what the <b>very first</b> request information the client sends to you 
he information between GET and HTTP/1.1. That is the file path which the client requires to display the website correctly on it's browser. <br /><br />

The <b>parse function</b> just retrieves the <b>path</b> and <b>file extension</b> (such as .jpg  .html  .css....) from a bunch of information. <br /> 
```c++
char* parse(char line[], const char symbol[])
{
    char *message;
    char * token = strtok(line, symbol);
    int current = 0;

    while( token != NULL ) {
      
      token = strtok(NULL, " ");
      if(current == 0){
          message = token;
          return message;
      }
      current = current + 1;
   }
   return message;
}
```

## 3.3 Classify the Request 
the Server need to tell the client what kind of content we are going to send in. The classification is just a bunch of <b>if else</b> logic detemination according to the file extension from the <b>parsed</b> information (section 3.2). I just list the partial code in the following to give you some concept.
 
 ```c++
 if(strlen(parse_string) <= 1){
            //case that the parse_string = "/"  --> Send index.html file
            //write(new_socket , httpHeader , strlen(httpHeader));
            char path_head[500] = ".";
            strcat(path_head, "/index.html");
            strcat(copy_head, "Content-Type: text/html\r\n\r\n");
            send_message(new_socket, path_head, copy_head);
}
else if ((parse_ext[0] == 'j' && parse_ext[1] == 'p' && parse_ext[2] == 'g') || 
(parse_ext[0] == 'J' && parse_ext[1] == 'P' && parse_ext[2] == 'G'))
{
            //send image to client
            char path_head[500] = ".";
            strcat(path_head, parse_string);
            strcat(copy_head, "Content-Type: image/jpeg\r\n\r\n");
            send_message(new_socket, path_head, copy_head);
}
else if (parse_ext[strlen(parse_ext)-2] == 'j' && parse_ext[strlen(parse_ext)-1] == 's')
{
            //javascript
            char path_head[500] = ".";
            strcat(path_head, parse_string);
            strcat(copy_head, "Content-Type: text/javascript\r\n\r\n");
            send_message(new_socket, path_head, copy_head);
}
else if (parse_ext[strlen(parse_ext)-3] == 'c' && parse_ext[strlen(parse_ext)-2] == 's' 
&& parse_ext[strlen(parse_ext)-1] == 's')
{
            //css
            char path_head[500] = ".";
            strcat(path_head, parse_string);
            strcat(copy_head, "Content-Type: text/css\r\n\r\n");
            send_message(new_socket, path_head, copy_head);
}
else if (parse_ext[0] == 'i' && parse_ext[1] == 'c' && parse_ext[2] == 'o')
{
            //https://www.cisco.com/c/en/us/support/docs/security/web-security-appliance/117995-qna-wsa-00.html
            char path_head[500] = ".";
            strcat(path_head, "/img/favicon.png");
            strcat(copy_head, "Content-Type: image/vnd.microsoft.icon\r\n\r\n");
            send_message(new_socket, path_head, copy_head);
}
 ```

The client's web browser will read line by line and do whatever the html file tells it. When it reads until line 14 (in above image), the client will send request to the server to ask for ```vendor/fontawesome-free/css/all.min.css``` which is a css file. Server than ```parse``` the request, and then classify the request. 

```c++
HTTP/1.1 200 Ok\r\n
Content-Type: text/html\r\n\r\n
```
You need to replace the ```text/html``` with the proper MIME Type according to the file extension. 
 
## 3.4 Reply to the Client
The following function first send notification message to the client and let it knows what kind of content we are going to send (section 3.3). We then open the file using ```open``` and retrieve information of the file (not the content) using ```fstat``` and store in ```stat object```. Lastly, we read the file content and send the content using ```sendfile```. Because some file might be too large to send in one message, thus, we need to send the content pices by pices (size = block_size).

```c++
int send_message(int fd, char image_path[], char head[]){

    struct stat stat_buf;  /* hold information about input file */

    write(fd, head, strlen(head));

    int fdimg = open(image_path, O_RDONLY);
     
    fstat(fdimg, &stat_buf);
    int img_total_size = stat_buf.st_size;
    int block_size = stat_buf.st_blksize;

    int sent_size;

    while(img_total_size > 0){
        if(img_total_size < block_size){
            sent_size = sendfile(fd, fdimg, NULL, img_total_size);            
        }
        else{
            sent_size = sendfile(fd, fdimg, NULL, block_size);
        }       
        printf("%d \n", sent_size);
        img_total_size = img_total_size - sent_size;
    }
    close(fdimg);
}
```

# 4. Summary
This is a simple, experimental but functional Ubuntu web server.
Is there a simple way? Yes, you can use <b>```Node.js```</b> which is a JavaScript runtime environment where you can build a simple web server in about 60 lines of code. 
```javascript
const http = require('http');
const path = require('path');
const fs = require('fs');

const server = http.createServer((req, res) => {
    let filePath = path.join(__dirname, req.url === '/' ? 'index.html' : req.url);
    let file_extname = path.extname(filePath);
    let contentType = 'text/html';

    switch(file_extname){
        case '.js':
            contentType = 'text/javascript';
            break;
        case '.css':
            contentType = 'text/css';
            break;
        case '.json':
            contentType = 'application/json';
            break;
        case '.png':
            contentType = 'image/png';
            break;
        case '.JPG':
            contentType = 'image/jpg';
            break;
        case '.ico':
            filePath = path.join(__dirname,'favicon.png');
            contentType = 'image/png';
            break;
        case '.ttf':
            contentType = 'font/ttf';
            break;
        case '.woff':
            contentType = 'font/woff';
            break;
        case '.woff2':
            contentType = 'font/woff2';
            break;
    }
    // Read File
    fs.readFile(filePath, (err, content) => {
        if(err){
            if(err.code == 'ENOENT'){
                console.log('Page not found');
            }
            else{
                res.writeHead(500);
                res.end('Server Error: ${err.code}');
            }
        }
        else{
            res.writeHead(200, {'Content-Type': contentType});
            res.end(content);    
        }
    });
});

const PORT = process.env.PORT || 8080;

server.listen(PORT, () => console.log(`Server is running and port is ${PORT}`));
```
