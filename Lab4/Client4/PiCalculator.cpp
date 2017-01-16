#include "stdafx.h"
#include "PiCalculator.h"


CPiCalculator::CPiCalculator()
{
}


CPiCalculator::~CPiCalculator()
{
}

int CPiCalculator::GetRandomNumber(int min, int max)
{
	std::random_device e;
	std::mt19937 gen(e());
	std::uniform_int_distribution<> range(min, max);
	return range(gen);
}

float CPiCalculator::CalculatePi(size_t iterationNum)
{
	int rad = 1000;
	int includedPoints = 0;
	for (auto i = 0; i < iterationNum; ++i)
	{
		int x = GetRandomNumber(0, rad);
		int y = GetRandomNumber(0, rad);
		if (std::pow(rad, 2) >= std::pow(x, 2) + std::pow(y, 2))
		{
			++includedPoints;
		}
	}
	return float(4.f * (float(includedPoints) / float(iterationNum)));
}