#include "stdafx.h"
#include "AbstractWorker.h"

void CAbstractWorker::TransformationMatrixToEchelonForm(size_t startIndex, size_t endIndex, std::shared_ptr<Matrix> matrix)
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
		divisionVector((*matrix)[i], (*matrix)[i][i]);
		for (size_t j = i + 1; j <matrix->size(); ++j)
		{
			minusVector((*matrix)[j], multiplyVector((*matrix)[i], (*matrix)[j][i]));
		}
	}
}

