#pragma once
#include "State.h"

class LambdaState :public State
{
public:
	bool isNullable() {
		return true;
	}
	std::vector<int> firstPos() {
		return std::vector<int>();
	}
	std::vector<int> lastPos() {
		return std::vector<int>();
	}

};