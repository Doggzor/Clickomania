#pragma once
#include <random>

static std::random_device rd;
static std::mt19937 mt(rd());
class Random
{
public:
	static int Int(int min, int max) {	
		return std::uniform_int_distribution<int>(min, max)(mt);
	}
	static float Float(float min, float max) {
		return std::uniform_real_distribution<float>(min, max)(mt);
	}
};
