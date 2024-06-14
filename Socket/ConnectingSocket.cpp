//
// Created by priyanshu on 10/6/24.
//

#include "ConnectingSocket.h"

HDE::ConnectingSocket::ConnectingSocket(int domain, int service, int type, int port,
										u_long interface):
		Socket(domain,service,type,port,interface)
{
	int connection=ConnectToSocket(getServer(),getAddress());
	setConnection(connection);
	Error(getConnection());
}


int HDE::ConnectingSocket::ConnectToSocket(int server, struct sockaddr_in address) {

	return connect(getServer(),(const struct sockaddr *)&address,sizeof(address));
}

