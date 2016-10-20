#include "stdafx.h"
#include "SuccessiveWorker.h"

CSuccessiveWorker::CSuccessiveWorker()
{
}

CSuccessiveWorker::~CSuccessiveWorker()
{
}

size_t CSuccessiveWorker::GetRang(Matrix const & matrix)
{
	m_matrix = std::make_shared<Matrix>(matrix);
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

	for (size_t i = 0; i < m_matrix->size(); ++i)
	{
		divisionVector((*m_matrix)[i], (*m_matrix)[i][i]);
		for (size_t j = i + 1; j <m_matrix->size(); ++j)
		{
			minusVector((*m_matrix)[j], multiplyVector((*m_matrix)[i], (*m_matrix)[j][i]));
		}
	}
	return CountRang();
}

size_t CSuccessiveWorker::CountRang()
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
