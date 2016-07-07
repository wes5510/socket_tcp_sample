#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#define SIZE sizeof (struct sockaddr_in)

int main()
{
	int sockfd;
	char c, rc;
	struct sockaddr_in server = {AF_INET, 7000};

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket call failed");
		exit(1);
	}

	if(connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
	{
		perror("connect call failed");
		exit(1);
	}

	for(rc = '\n';;)
	{
		if(rc == '\n')
			printf("Input a lower case character\n");
		c = getchar();
		send(sockfd, &c, 1, 0);
		if(recv(sockfd, &rc, 1, 0) > 0)
			printf("%c", rc);
		else
		{
			printf("server has died\n");
			close(sockfd);
			exit(1);
		}
	}
	return 0;
}
