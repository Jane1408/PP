#include "stdafx.h"
#include "PipeHelper.h"


CPipeHelper::CPipeHelper()
{
}


CPipeHelper::~CPipeHelper()
{
}

void CPipeHelper::WaitingMassages(std::vector<std::string>& messages, size_t massageNumber, std::string const& pipeName)
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

void CPipeHelper::SendMassage(std::string const & massage, std::string const& pipeName)
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