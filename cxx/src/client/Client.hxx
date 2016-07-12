#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cstdio>

#include <string>
#include <stdexcept>

#define SIZE sizeof(struct sockaddr_in)

class Client
{
	private:
		int sockfd;
		static int newsockfd;
		struct sockaddr_in server;
		static bool exit_loop;
		void work();
	public:
		Client(const int port, const char* ip_addr);
		~Client();
		void connect();
};

#endif
