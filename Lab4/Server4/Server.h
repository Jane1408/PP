#pragma once
class CServer
{
public:
	CServer(size_t processCount, size_t iterationCount);
	~CServer();

	void StartServer();

private:
	void WaitMessages(std::vector<std::string>& messages, size_t massageNumber, std::string const& pipeName);
	void SendMessage(std::string const & massage, std::string const& pipeName);
	size_t m_processCount;
	size_t m_iterationsCount;
};

