#pragma once
class CPipeHelper
{
public:
	CPipeHelper();
	~CPipeHelper();
	static void WaitingMassages(std::vector<std::string>& messages, size_t massageNumber, std::string const& pipeName);
	static void SendMassage(std::string const & massage, std::string const& pipeName);
};

