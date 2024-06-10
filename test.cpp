//
// Created by priyanshu on 11/6/24.
//

#include "Socket/ListeningSocket.h"
#include "iostream"
using namespace std;

int main()
{

	cout << "startlistening" << "\n";
	HDE::ListeningSocket ls=HDE::ListeningSocket(AF_INET, SOCK_STREAM, 0,
												 80,INADDR_ANY,0);
	cout << "listening end" << "\n";
}
