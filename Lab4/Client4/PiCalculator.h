#pragma once
class CPiCalculator
{
public:
	CPiCalculator();
	~CPiCalculator();

	static float CalculatePi(size_t iterationNum);
	static int GetRandomNumber(int min, int max);
};

