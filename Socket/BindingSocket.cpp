//
// Created by priyanshu on 10/6/24.
//

#include "BindingSocket.h"

HDE::BindingSocket::BindingSocket(int domain, int service, int type, int port, u_long interface):
		Socket(domain,service,type,port,interface)
{
	int connection=ConnectToSocket(getServer(),getAddress());
	setConnection(connection);
	Error(getConnection());
}


int HDE::BindingSocket::ConnectToSocket(int server, struct sockaddr_in address) {

	return bind(server,(struct sockaddr_in*)&address,sizeof(address));
}


