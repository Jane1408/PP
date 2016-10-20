#pragma once
#include "AbstractWorker.h"
class CParallelWorker :
	public CAbstractWorker
{
public:
	CParallelWorker();
	~CParallelWorker();

	void SetThreadCount(size_t value);
	size_t GetRang(Matrix const& matrix) override;
private:
	size_t CountRang() override;
	std::shared_ptr<Matrix> m_matrix;
	std::vector<std::thread> m_threads;

	size_t m_threadsCounter;
};

