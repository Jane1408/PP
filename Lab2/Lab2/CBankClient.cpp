#include "stdafx.h"
#include "CBankClient.h"

namespace
{
	int GetRandomNumber(int max, int min)
	{
		std::random_device e;
		std::mt19937 gen(e());
		std::uniform_int_distribution<> range(min, max);
		return range(gen);
	}
}

CBankClient::CBankClient(CBank *bank, unsigned int id, Primitives *primitives)
	: m_syncPrimitives(primitives)
	, m_bank(bank)
	, m_id(id)
{}

unsigned int CBankClient::GetId()
{
	return m_id;
}

void SomeLongOperation(unsigned time)
{
	Sleep(time);
}

std::function<void(CBankClient*)> CBankClient::GetSyncMethodFunc(PrimitiveType type)
{

	std::function<void(CBankClient*)> func;
	switch (type)
	{
	case PrimitiveType::CRITICAL_SECTION:
		func = [](CBankClient * client) {
			EnterCriticalSection(&client->m_syncPrimitives->critical_section);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			LeaveCriticalSection(&client->m_syncPrimitives->critical_section);
		};
		break;
	case PrimitiveType::SEMAPHORE:
		func = [](CBankClient * client) {
			WaitForSingleObject(client->m_syncPrimitives->hSemaphore, INFINITE);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			ReleaseSemaphore(client->m_syncPrimitives->hSemaphore, 1, NULL);
		};
		break;
	case PrimitiveType::MUTEX:
		func = [](CBankClient * client) {
			WaitForSingleObject(client->m_syncPrimitives->hMutex, INFINITE);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			ReleaseMutex(client->m_syncPrimitives->hMutex);
		};
		break;
	case PrimitiveType::EVENT:
		func = [](CBankClient * client) {
			WaitForSingleObject(client->m_syncPrimitives->hEvent, INFINITE);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			SetEvent(client->m_syncPrimitives->hEvent);
		};
		break;
	case PrimitiveType::NO:
		func = [](CBankClient * client) {
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
		};
		break;
	default:
		break;
	}
	return func;
}

DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	
	CBankClient *client = (CBankClient*)lpParam;
	
	srand(client->m_id);
	
	while (true)
	{
		SomeLongOperation(GetSleepDuration(client));
		GetSyncMethodFunc(client->m_syncPrimitives->type)(client);
	}
	
	return 0;
}

unsigned int CBankClient::GetSleepDuration(CBankClient *client)
{
	return GetRandomNumber(1000, 3999);
}


unsigned int CBankClient::GetBalanceChangeValue()
{
	return GetRandomNumber(-100, 100);
}