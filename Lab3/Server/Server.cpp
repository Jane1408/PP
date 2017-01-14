#include "stdafx.h"
#include "Server.h"


CServer::CServer(size_t processCount, size_t iterationCount)
	: m_processCount(processCount)
	, m_iterationsCount(iterationCount)
{
}


CServer::~CServer()
{
}

void CServer::StartServer()
{
	std::vector<std::string> massagesList;

	for (auto i = 0; i < m_processCount; ++i)
	{
		std::string commandLine = "Client.exe Process" + std::to_string(i) + " " + std::to_string(m_iterationsCount);
		auto foo = [](std::string const& com) {system(com.c_str()); };
		std::thread th(std::bind(foo, commandLine));
		th.detach();

	}
	WaitingMassages(std::ref(massagesList), m_processCount);

	for (auto& it : massagesList)
	{
		std::cout<< it << std::endl;
	}


}

void CServer::WaitingMassages(std::vector<std::string>& messages, size_t massageNumber)
{
	HANDLE hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\mpipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		1024, 1024, 5000, NULL);

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed" << std::endl;
		return;
	}

	size_t massageCount = 0;
	while (massageCount < massageNumber)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			char buffer[1024];
			DWORD dwRead;
			if (ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL) == TRUE)
			{
				buffer[dwRead] = '\0';
			}
			messages.push_back(buffer);
			++massageCount;
		}
		DisconnectNamedPipe(hPipe);
	}
	CloseHandle(hPipe);
}

