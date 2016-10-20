#include "stdafx.h"
#include "RangFinder.h"
#include <thread>

CRangFinder::CRangFinder()
{
}


CRangFinder::~CRangFinder()
{
}

void CRangFinder::SetMatrix(Matrix const & matrix)
{
	m_matrix = std::make_shared<Matrix>(matrix);
}

void CRangFinder::SetThreadCount(size_t value)
{
	m_threadsCounter = std::max(value, size_t(1));
	m_threadsCounter = std::min(m_threadsCounter, size_t(16));
}

void WorkWithPart(size_t startIndex, size_t endIndex, std::shared_ptr<Matrix> m_matrix)
{
	auto divisionVector = [&](std::vector<double> &vec, double number)
	{
		for (auto &it : vec)
		{
			it /= number;
		}
	};
	auto multiplyVector = [&](std::vector<double> vec, double number)
	{
		auto returnedVec = vec;
		for (auto &it : returnedVec)
		{
			it *= number;
		}
		return returnedVec;
	};
	auto minusVector = [&](std::vector<double> &vec, std::vector<double> vec1)
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			vec[i] -= vec1[i];
		}
	};

	for (size_t i = startIndex; i < endIndex; ++i)
	{
		divisionVector((*m_matrix)[i], (*m_matrix)[i][i]);
		for (size_t j = i + 1; j < m_matrix->size(); ++j)
		{
			minusVector((*m_matrix)[j], multiplyVector((*m_matrix)[i], (*m_matrix)[j][i]));
		}
	}
}

size_t CRangFinder::FindRang()
{
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
		m_threads[i] = std::thread(WorkWithPart, startIndex, endIndex, m_matrix);
	}
	for (auto &it : m_threads)
	{
		it.join();
	}
	return GetRang();
}

size_t CRangFinder::GetRang()
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


