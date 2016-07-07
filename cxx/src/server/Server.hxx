#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>

#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <cctype>

#define SIZE sizeof(struct sockaddr_in)

class Server
{
	private:
		int sockfd;
		static int newsockfd;
		struct sockaddr_in server;
		static bool exit_loop;
		void init_server_addr(const int port, const char* ip_addr);
		void init_signal();
		static void signal_handler(int signo);
		void to_listen();
	public:
		Server(const int port, const char* ip_addr);
		~Server();
		void run();
};

#endif
