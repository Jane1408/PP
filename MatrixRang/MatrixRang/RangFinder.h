#pragma once
typedef std::vector<std::vector<double>> Matrix;

class CRangFinder
{
public:
	CRangFinder();
	~CRangFinder();

	void SetThreadCount(size_t value);
	size_t GetRang(Matrix const& matrix);

private:
	size_t CountRang();
	std::shared_ptr<Matrix> m_matrix;
	std::vector<std::thread> m_threads;

	size_t m_threadsCounter;
};

