#include "stdafx.h"
#include "random.h"

int GetRandomNumber(int min, int max)
{
	std::random_device e;
	std::mt19937 gen(e());
	std::uniform_int_distribution<> range(min, max);
	return range(gen);
}