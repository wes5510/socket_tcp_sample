#include "Client.hxx"

int main()
{
	Client client(7000, "127.0.0.1");

	try
	{
		client.connect();
	}
	catch(const std::exception& e)
	{
		printf("%s", e.what());
	}

	return 0;
}
