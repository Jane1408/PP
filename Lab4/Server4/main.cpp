// Server.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Server.h"
namespace
{
	const std::string USAGE = "Error!!! Usage Server.exe <Iterations count> <Process count>";
	//TODO: отдельной функцией
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << USAGE << std::endl;
		return 1;
	}
	CServer server(std::atoi(argv[2]), std::atoi(argv[1]));
	server.StartServer();
    return 0;
}

