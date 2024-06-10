//
// Created by priyanshu on 10/6/24.
//

#ifndef WEB_SERVER_CONNECTINGSOCKET_H
#define WEB_SERVER_CONNECTINGSOCKET_H


#include"Create_socket.h"

namespace HDE{
	class ConnectingSocket:public Socket {
	private:

	public:
		ConnectingSocket(int domain,int service, int type,int port,u_long interface);
		int 		ConnectToSocket(int server,struct sockaddr_in address);
	};
};
#endif //WEB_SERVER_CONNECTINGSOCKET_H
