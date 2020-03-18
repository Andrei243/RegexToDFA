#pragma once
#include "State.h"


class DotState :public State {
private:
	State* stateLeft;
	State* stateRight;
public:
	DotState(State* stateLeft, State* stateRight) {
		this->stateLeft = stateLeft;
		this->stateRight = stateRight;
	}
	bool isNullable() {
		return stateLeft->isNullable() && stateRight->isNullable();
	}
	std::vector<int> firstPos() {
		return appendUnique(stateLeft->firstPos(), !isNullable() ? std::vector<int>() : stateRight->firstPos());
	}

	std::vector<int> lastPos() {
		return appendUnique(stateRight->lastPos(), !isNullable() ? std::vector<int>() : stateLeft->lastPos());
	}
	void calculateFollowers(std::vector<std::vector<int>>& followersMatrix) {
		stateLeft->calculateFollowers(followersMatrix);
		stateRight->calculateFollowers(followersMatrix);
		for (int i : stateLeft->lastPos()) {
			for (int j : stateRight->firstPos()) {
				followersMatrix[i].push_back(j);
			}
		}

	}

};