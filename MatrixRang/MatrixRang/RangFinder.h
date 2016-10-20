#pragma once
typedef std::vector<std::vector<double>> Matrix;

class CRangFinder
{
public:
	CRangFinder();
	~CRangFinder();

	void SetMatrix(Matrix const& matrix);
	void SetThreadCount(size_t value);
	size_t FindRang();


private:
	size_t GetRang();
	std::shared_ptr<Matrix> m_matrix;
	std::vector<std::thread> m_threads;

	size_t m_threadsCounter;
};

