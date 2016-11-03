#pragma once
#include "MatrixType.h"

class CAbstractWorker
{
public:
	virtual size_t GetRang(Matrix const& matrix) = 0;
	static void TransformationMatrixToEchelonForm(size_t startIndex, size_t endIndex, std::shared_ptr<Matrix> matrix);


protected:
	virtual size_t CountRang() = 0;
};

