#pragma once
#include "CBankClient.h"
class CBankClient;

class CBank
{
public:
	CBank(PrimitiveType type);
	~CBank();
	std::shared_ptr<CBankClient> CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	size_t GetClientsCount() const;
	HANDLE* GetClientsHandles() const;
	DWORD WaitForClients();
private:
	std::vector<std::shared_ptr<CBankClient>> m_clients;
	int m_totalBalance;
	std::shared_ptr<Primitives> m_syncPrimitives;

	
	int GetTotalBalance();
	void SetTotalBalance(int value);
	void SomeLongOperations(CBankClient const &client);

};