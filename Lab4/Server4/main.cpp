// Server.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Server.h"
namespace
{

	void ShowUsage()
	{
		std::cout << "Error!!!Usage Server.exe <Iterations count> <Process count>" << std::endl;
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		ShowUsage();
		return 1;
	}
	CServer server(std::atoi(argv[2]), std::atoi(argv[1]));
	server.StartServer();
    return 0;
}

