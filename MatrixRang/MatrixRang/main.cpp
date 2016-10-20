// MatrixRang.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixType.h"
#include "CreateMatrix.h"
#include "SuccessiveWorker.h"
#include "ParallelWorker.h"

int main(int argc, char * argv[])
{
	Matrix matr = CreateMatrix(1000);
	size_t time = 0;
	size_t finishTime = 0;
	if (argc == 2)
	{
		size_t threadCount = std::atoi(argv[1]);
		CParallelWorker pWoker;
		time = clock();
		pWoker.SetThreadCount(threadCount);
		size_t rang = pWoker.GetRang(matr);
		finishTime = clock();
	}
	else
	{
		CSuccessiveWorker sWoker;
		time = clock();
		size_t rang = sWoker.GetRang(matr);
		finishTime = clock();
	}
	std::cout << (finishTime - time) / 1000.0 << std::endl;
    return 0;
}

