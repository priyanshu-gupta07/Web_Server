//
// Created by Priyanshu Gupta on 8/6/24.
//

#include "Create_socket.h"

HDE::Socket::Socket(int domain, int service, int type,int port,u_long interface) {
	//Defining Address for Connection
	address.sin_family=domain;
	address.sin_port= htons(port);
	address.sin_addr.s_addr= htonl(interface);
	//Creating Socket
	server_fd= socket(domain,service,type);
	//Testing Socket
	Error(server_fd);
	//Creating Connection
	connection= ConnectToSocket(server_fd,address);
	//testing Connection
	Error(connection);
}

void HDE::Socket::Error(int item) {
	//testing the item
	if(item<0){
		perror("ERROR IN SOCKET CREATION");
		exit(EXIT_FAILURE);
	}
}

//getter Function
int HDE::Socket::getServer() {
	return server_fd;
}

int HDE::Socket::getConnection() {
	return connection;
}


