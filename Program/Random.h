#pragma once
#include <random>

class Random
{
public:
	Random() : mt(rd()) {}
	int RandInt(int min, int max) {		
		return std::uniform_int_distribution<int>(min, max)(mt);
	}
private:
	std::random_device rd;
	std::mt19937 mt;
};
