#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#define SIZE sizeof (struct sockaddr_in)

void catcher(int sig);
int newsockfd;

int main()
{
	int sockfd;
	char c;
	struct sockaddr_in server = {AF_INET, 7000};

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	signal(SIGPIPE, catcher);
	signal(SIGCHLD, SIG_IGN);

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
	
	while(1)
	{
		if((newsockfd = accept(sockfd, NULL, NULL)) == -1)
		{
			perror("accept call failed");
			continue;
		}

		if(fork() == 0)
		{
			while(recv(newsockfd, &c, 1, 0))
			{
				c = toupper(c);
				send(newsockfd, &c, 1, 0);
			}
			close(newsockfd);
			exit(0);
		}

		close(newsockfd);
	}

	return 0;
}

void catcher(int sig)
{
		close(newsockfd);
		exit(0);
}
