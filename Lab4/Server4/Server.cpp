#include "stdafx.h"
#include "Server.h"

namespace
{
	const std::string GET_PI_PIPE = "\\\\.\\pipe\\mpipe";
	const std::string START_WORK_PIPE = "\\\\.\\pipe\\StartPipe";
	const std::string READY_PIPE = "\\\\.\\pipe\\readypipe";
}

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


	WaitingMassages(std::vector<std::string>(), m_processCount, READY_PIPE);
	std::cout << "Clients ready" << std::endl;
	system("pause");

	for (auto i = 0; i < m_processCount; ++i)
	{
		SendMassage(std::to_string(m_iterationsCount), START_WORK_PIPE);
	}

	WaitingMassages(std::ref(massagesList), m_processCount, GET_PI_PIPE);
}

void CServer::WaitingMassages(std::vector<std::string>& messages, size_t massageNumber, std::string const& pipeName)
{
	std::wstring wName(pipeName.begin(), pipeName.end());
	HANDLE hPipe = CreateNamedPipe(wName.data(),
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
			std::cout << buffer << std::endl;
			++massageCount;
		}
		DisconnectNamedPipe(hPipe);
	}
	CloseHandle(hPipe);
}


void CServer::SendMassage(std::string const & massage, std::string const& pipeName)
{
	HANDLE hPipe;
	std::wstring wName(pipeName.begin(), pipeName.end());
	do
	{
		hPipe = CreateFile(wName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	} while (hPipe == INVALID_HANDLE_VALUE);

	DWORD dwWritten = static_cast<DWORD>(massage.size());
	if (hPipe != INVALID_HANDLE_VALUE)
	{
		while (WriteFile(hPipe, massage.data(), static_cast<DWORD>(massage.size()), &dwWritten, NULL) == FALSE)
		{
		}
		CloseHandle(hPipe);
	}
}