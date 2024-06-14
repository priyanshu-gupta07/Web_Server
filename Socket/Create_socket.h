//
// Created by priyanshu on 8/6/24.
//

#ifndef WEB_SERVER_CREATE_SOCKET_H
#define WEB_SERVER_CREATE_SOCKET_H

#include "sys/socket.h"
#include "stdio.h"
#include "stdlib.h"
#include <netinet/in.h>
#include <sys/types.h>

namespace HDE{
	class Socket {
	private:
		int 							server_fd;
		struct sockaddr_in				address;
		int								connection;
	public:
		//constructor for creating a Socket
		Socket(int domain,int service, int type,int port,u_long interface);
		void		Error(int);
		//Establishing Connection With Socket
		virtual int			ConnectToSocket(int server,struct sockaddr_in address)=0;
		//Getter Functions
		int					getServer();
		int					getConnection();
		void				setConnection(int connection);
		struct sockaddr_in	getAddress();
	};
}

#endif //WEB_SERVER_CREATE_SOCKET_H
