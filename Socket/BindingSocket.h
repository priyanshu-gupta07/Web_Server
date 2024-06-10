//
// Created by priyanshu on 10/6/24.
//

#ifndef WEB_SERVER_BINDINGSOCKET_H
#define WEB_SERVER_BINDINGSOCKET_H

#include"Create_socket.h"

namespace HDE{
	class BindingSocket:public Socket {
	private:

	public:
		BindingSocket(int domain,int service, int type,int port,u_long interface);
		int 		ConnectToSocket(int server,struct sockaddr_in address);

	};
};

#endif //WEB_SERVER_BINDINGSOCKET_H
