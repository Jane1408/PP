#include "stdafx.h"

namespace
{
	const std::string SEND_PIPE = "\\\\.\\pipe\\mpipe";
	const std::string READY_PIPE = "\\\\.\\pipe\\readypipe";

	int GetRandomNumber(int min, int max)
	{
		std::random_device e;
		std::mt19937 gen(e());
		std::uniform_int_distribution<> range(min, max);
		return range(gen);
	}

	float CalculatePi(size_t iterationNum)
	{
		int rad = 1000;
		int includedPoints = 0;
		for (auto i = 0; i < iterationNum; ++i)
		{
			int x = GetRandomNumber(0, rad);
			int y = GetRandomNumber(0, rad);
			if (std::pow(rad, 2) >= std::pow(x, 2) + std::pow(y, 2))
			{
				++includedPoints;
			}
		}
		return float(4.f * (float(includedPoints) / float(iterationNum)));
	}

	void SendMassage(std::string const & massage, std::string const& pipeName)
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

	void PrepearingAndSendMassage(std::string const& name, size_t const& iterationCount, double const& calculatedPi)
	{
		std::string str = "Process " + name +
			" " + std::to_string(iterationCount) + " PI = " + std::to_string(calculatedPi);
		SendMassage(str, SEND_PIPE);
	}

	size_t WaitingMassages()
	{
		size_t iterCount = 0;
		HANDLE hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\StartPipe"),
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			1024, 1024, 5000, NULL);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			std::cout << "Failed" << std::endl;
			return 0;
		}

		size_t massageCount = 0;
		while (massageCount < 1)
		{
			if (ConnectNamedPipe(hPipe, NULL) != FALSE)
			{
				char buffer[1024];
				DWORD dwRead;
				if (ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL) == TRUE)
				{
					buffer[dwRead] = '\0';
				}
				iterCount = size_t(std::atoi(buffer));
				++massageCount;
			}
			DisconnectNamedPipe(hPipe);
		}
		CloseHandle(hPipe);
		return iterCount;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	auto procName = argv[1];
	SendMassage("Process " + std::string(procName) + " Ready to work", READY_PIPE);
	auto iterCount = WaitingMassages();
	PrepearingAndSendMassage(procName, iterCount, CalculatePi(iterCount));
	return 0;
}

