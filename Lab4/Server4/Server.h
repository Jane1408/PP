#pragma once
class CServer
{
public:
	CServer(size_t processCount, size_t iterationCount);
	~CServer();

	void StartServer();

private:
	void WaitingMassages(std::vector<std::string>& messages, size_t massageNumber, std::string const& pipeName);
	void SendMassage(std::string const & massage, std::string const& pipeName);
	size_t m_processCount;
	size_t m_iterationsCount;
};

