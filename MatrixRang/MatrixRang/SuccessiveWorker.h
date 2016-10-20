#pragma once
#include "AbstractWorker.h"

class CSuccessiveWorker :
	public CAbstractWorker
{
public:
	CSuccessiveWorker();
	~CSuccessiveWorker();

	size_t GetRang(Matrix const& matrix) override;
private:
	size_t CountRang() override;
	std::shared_ptr<Matrix> m_matrix;
};

