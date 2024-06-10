//
// Created by priyanshu on 10/6/24.
//

#ifndef WEB_SERVER_LISTENING_H
#define WEB_SERVER_LISTENING_H

#include "BindingSocket.h"

namespace HDE{
	class ListeningSocket:public BindingSocket{
	private:
		int backlog;
		int listening;
	public:
						ListeningSocket(int domain, int service, int type, int port,
						u_long interface,int blkg);
		void			StartListening();


	};
}
#endif //WEB_SERVER_LISTENING_H
