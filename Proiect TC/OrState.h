#pragma once
#include "State.h"

class OrState :public State {

	State* stateLeft;
	State* stateRight;
public:
	OrState(State* stateLeft, State* stateRight) {
		this->stateLeft = stateLeft;
		this->stateRight = stateRight;
	}
	bool isNullable() {
		return stateLeft->isNullable() || stateRight->isNullable();
	}
	std::vector<int> firstPos() {
		return appendUnique(stateLeft->firstPos(),  stateRight->firstPos());
	}

	std::vector<int> lastPos() {
		return appendUnique(stateRight->lastPos(),  stateLeft->lastPos());
	}
	void calculateFollowers(std::vector<std::vector<int>>& followersMatrix) {
		stateLeft->calculateFollowers(followersMatrix);
		stateRight->calculateFollowers(followersMatrix);

	}

};