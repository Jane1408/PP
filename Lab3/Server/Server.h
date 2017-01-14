#pragma once
class CServer
{
public:
	CServer(size_t processCount, size_t iterationCount);
	~CServer();

	void StartServer();

private:
	void WaitingMassages(std::vector<std::string>& messages, size_t massageNumber);

	size_t m_processCount;
	size_t m_iterationsCount;
};

