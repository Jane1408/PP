#pragma once
class CPipeHelper
{
public:
	CPipeHelper();
	~CPipeHelper();
	static void WaitMessages(std::vector<std::string>& messages, size_t massageNumber, std::string const& pipeName);
	static void SendMessage(std::string const & massage, std::string const& pipeName);
};

