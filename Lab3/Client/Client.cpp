// Client.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


namespace
{
	const std::string PIPE_TO_SEND_PI = "\\\\.\\pipe\\mpipe";

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

	void SendByPipe(std::string const & massage, std::string const& pipeName)
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

	void SendMassage(std::string const& procName, size_t const& iterationNum, double const& calculatedPi)
	{
		std::string str = "Process " + procName +
			" " + std::to_string(iterationNum) + " PI = " + std::to_string(calculatedPi);
		SendByPipe(str, PIPE_TO_SEND_PI);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		return 1;
	auto procName = argv[1];
	auto iterCount = std::atoi(argv[2]);
	SendMassage(procName, iterCount, CalculatePi(iterCount));
	return 0;
}

