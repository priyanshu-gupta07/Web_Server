//
// Created by priyanshu on 11/6/24.
//

#include "../Socket/ListeningSocket.h"
#include "../Socket/systemdependies.h"
#include<iostream>

namespace HDE {
	class SimpleServer {
		private:
			ListeningSocket*		Socket;

		public:
			SimpleServer(int domain, int service, int type, int port, u_long interface,int backlog);
			virtual void		AcceptConnection()=0;
			virtual void		handleConnection()=0;
			virtual void		respondConnection()=0;
			virtual void		launch()=0;
			ListeningSocket*	getSocket();
			
	};
}
