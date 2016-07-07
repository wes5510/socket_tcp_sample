#include "Server.hxx"

int main()
{
	Server server(7000, "127.0.0.1");

	server.run();

	return 0;
}
