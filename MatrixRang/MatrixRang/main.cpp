// MatrixRang.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RangFinder.h"


Matrix GetMatrix(size_t n)
{
	std::mt19937 rng;
	std::uniform_int_distribution<>num(0, 100);
	Matrix matrix;
	matrix.resize(n);
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			matrix[i].push_back(num(rng));
		}
	}
	return matrix;
}

int main(int argc, char * argv[])
{
	size_t threadCount = (argc == 2) ? std::atoi(argv[1]) : 1 ;
	Matrix matr = GetMatrix(1000);
	CRangFinder worker;
	size_t time = clock();
	worker.SetMatrix(matr);
	worker.SetThreadCount(threadCount);
	size_t rang = worker.FindRang();
	size_t finishTime = clock();
	std::cout << (finishTime - time) / 1000.0 << std::endl;
    return 0;
}

