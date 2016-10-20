#pragma once
#include "MatrixType.h"

class CAbstractWorker
{
public:
	virtual size_t GetRang(Matrix const& matrix) = 0;

protected:
	virtual size_t CountRang() = 0;
};

