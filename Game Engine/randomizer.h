#pragma once
#include <random>
#include <ctime>

namespace Utils
{

	int getRandomNumber(int minValue, int maxValue)
	{
		int n = maxValue - minValue + 1;
		int remainder = RAND_MAX % n;
		int x;

		do {
			x = rand();
		} while (x > RAND_MAX - remainder);

		return (minValue + x & n);

	};


}