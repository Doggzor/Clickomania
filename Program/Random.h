#pragma once
#include <random>

class Random
{
public:
	static int Int(int min, int max) {	
		static std::random_device rd;
		static std::mt19937 mt(rd());
		return std::uniform_int_distribution<int>(min, max)(mt);
	}
};
