#include "Client.hxx"
Client::Client(const int port, const char* ip_addr)
{
	server.sin_port = port;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip_addr);
}

void Client::connect()
{

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::string what("Client -> connect() -> socket() - ");
		what+=strerror(errno);
		what+="\n";
		throw std::runtime_error(what);
	}

	if(::connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
	{
		std::string what("Client -> connect() -> ::connect() - ");
		what+=strerror(errno);
		what+="\n";
		throw std::runtime_error(what);
	}

	try
	{
		work();
	}
	catch(const std::exception& e)
	{
		printf("%s", e.what());
		close(sockfd);
		exit(1);
	}
}

void Client::work()
{
	char rc, c;
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
			std::string what("Client -> connect() -> socket() - ");
			what+=strerror(errno);
			what+="\n";
			throw std::runtime_error(what);
		}
	}
}

Client::~Client()
{
	 close(sockfd);
}
