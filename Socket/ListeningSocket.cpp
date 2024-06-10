//
// Created by priyanshu on 10/6/24.
//

#include "ListeningSocket.h"

HDE::ListeningSocket::ListeningSocket(int domain, int service, int type, int port, u_long interface,
										int blkg):
		BindingSocket(domain,service,type,port,interface)
{
	backlog=blkg;
	StartListening();
	Error(listening);
}

void HDE::ListeningSocket::StartListening() {
	listening= listen(getServer(),backlog);
}

