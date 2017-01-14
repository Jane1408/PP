#pragma once
#include "CBank.h"
class CBank;

class CBankClient
{
public:
	unsigned int GetId();
	~CBankClient() = default;
private:
	unsigned m_id;
	CBank *m_bank;

	CBankClient(CBank *bank, unsigned int id, Primitives *syncPrimitives);
	
	static unsigned int GetSleepDuration(CBankClient *client);
	static unsigned int GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	static std::function<void(CBankClient*)> GetSyncMethodFunc(PrimitiveType type);

	friend CBank;

	HANDLE m_handle;
	Primitives *m_syncPrimitives = nullptr;

};