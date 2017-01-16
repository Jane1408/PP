#include "stdafx.h"
#include "PiCalculator.h"
#include "PipeHelper.h"
namespace
{
	const std::string SEND_PIPE = "\\\\.\\pipe\\mpipe";
	const std::string READY_PIPE = "\\\\.\\pipe\\readypipe";
	const std::string START_PIPE = "\\\\.\\pipe\\StartPipe";


	void PrepearAndSendMessage(std::string const& name, size_t const& iterationCount, double const& calculatedPi)
	{
		std::string str = "Process " + name +
			" " + std::to_string(iterationCount) + " PI = " + std::to_string(calculatedPi);
		CPipeHelper::SendMessage(str, SEND_PIPE);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	auto procName = argv[1];
	CPipeHelper::SendMessage("Process " + std::string(procName) + " Ready to work", READY_PIPE);
	std::vector<std::string> messages;
	CPipeHelper::WaitMessages(messages, 1, START_PIPE);
	size_t iterCount = std::atoi(messages[0].c_str());
	PrepearAndSendMessage(procName, iterCount, CPiCalculator::CalculatePi(iterCount));
	return 0;
}

