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
	TransformationMatrixToEchelonForm(0, m_matrix->size(), m_matrix);
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
