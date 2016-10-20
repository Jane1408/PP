#pragma once
#include "stdafx.h"

Matrix CreateMatrix(size_t n)
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