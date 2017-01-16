#include "stdafx.h"
#include "Server.h"
#include "../Client4/PipeHelper.h"
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
	std::vector<std::string> messageList;


	CPipeHelper::WaitMessages(std::vector<std::string>(), m_processCount, READY_PIPE);
	std::cout << "Clients ready" << std::endl;
	system("pause");

	for (auto i = 0; i < m_processCount; ++i)
	{
		CPipeHelper::SendMessage(std::to_string(m_iterationsCount), START_WORK_PIPE);
	}

	CPipeHelper::WaitMessages(std::ref(messageList), m_processCount, GET_PI_PIPE);
}