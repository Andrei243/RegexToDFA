#pragma once
#include "State.h"

class NodeState :public State {
	int position;
	char character;
public:
	NodeState(int position, char character) {
		this->position = position;
		this->character = character;
	}

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