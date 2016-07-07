#include "Server.hxx"

bool Server::exit_loop = false;
int Server::newsockfd = -1;

Server::Server(const int port, const char* ip_addr)
{
	init_server_addr(port, ip_addr);
	init_signal();
}

void Server::init_server_addr(const int port, const char* ip_addr)
{
	server = {AF_INET, port};
	server.sin_addr.s_addr = inet_addr(ip_addr); 
}

void Server::init_signal()
{
	signal(SIGPIPE, signal_handler);
	signal(SIGCHLD, SIG_IGN);
}

void Server::signal_handler(int signo)
{
	if(newsockfd == -1)
	{
		close(newsockfd);
		newsockfd = -1;
	}
	exit_loop = true;
}

void Server::run()
{
	char c = '\0';

	to_listen();

	while(!exit_loop)
	{
		if((newsockfd = accept(sockfd, NULL, NULL)) == -1)
		{                                                                                                            
			perror("accept call failed");
			continue;
		}

		if(fork() == 0)
		{
			while(recv(newsockfd, &c, 1, 0) && !exit_loop)
			{
				c = toupper(c);
				send(newsockfd, &c, 1, 0);
			}
			return;
		}
	}

	return;
}

void Server::to_listen()
{
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket call failed");
		exit(1);
	}

	if(bind(sockfd, (struct sockaddr *) &server, SIZE) == -1)
	{
		perror("bind call failed");
		exit(1);
	}

	if(listen(sockfd, 5) == -1)
	{
		perror("listen call failed");
		exit(1);
	}
}

Server::~Server()
{
	if(newsockfd == -1)
	{
		close(newsockfd);
		newsockfd = -1;
	}
}
