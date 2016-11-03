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
	size_t threadCount = (argc == 2) ? std::atoi(argv[1]) : 1;
	
	if (threadCount > 1)
	{
		CParallelWorker pWorker;
		time = clock();
		pWorker.SetThreadCount(threadCount);
		size_t rang = pWorker.GetRang(matr);
		finishTime = clock();
	}
	else
	{
		CSuccessiveWorker sWorker;
		time = clock();
		size_t rang = sWorker.GetRang(matr);
		finishTime = clock();
	}
	std::cout << (finishTime - time) / 1000.0 << std::endl;
    return 0;
}

