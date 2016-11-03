#include "stdafx.h"
#include "ParallelWorker.h"
#include <thread>

CParallelWorker::CParallelWorker()
{
}

CParallelWorker::~CParallelWorker()
{
}

void CParallelWorker::SetThreadCount(size_t value)
{
	m_threadsCounter = std::min(std::max(value, size_t(1)), size_t(16));
}

size_t CParallelWorker::GetRang(Matrix const & matrix)
{
	m_matrix = std::make_shared<Matrix>(matrix);
	m_threads.clear();
	size_t step = size_t(m_matrix->size() / m_threadsCounter);
	m_threads.resize(m_threadsCounter);
	for (size_t i = 0; i < m_threadsCounter; ++i)
	{
		size_t  startIndex = i * step;
		size_t endIndex = startIndex + step;
		if (i == m_threadsCounter - 1)
		{
			endIndex = m_matrix->size() - 1;
		}
		m_threads[i] = std::thread(TransformationMatrixToEchelonForm, startIndex, endIndex, m_matrix);
	}
	for (auto &it : m_threads)
	{
		it.join();
	}
	return CountRang();
}

size_t CParallelWorker::CountRang()
{
	size_t rang = 0;
	for (auto &i : *m_matrix)
	{
		for (auto &j : i)
		{
			if (j != 0)
			{
				++rang;
				break;
			}
		}
	}
	return rang;
}
