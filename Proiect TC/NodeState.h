#pragma once
#include "State.h"

class NodeState :public State {
public:
	bool isNullable() {
		return false;
	}
	std::vector<int> firstPos() {
		return std::vector<int>(1,position);
	}
	std::vector<int> lastPos() {
		return std::vector<int>(1, position);
	}
	

};