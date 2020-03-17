#pragma once
#include "State.h"

class StarState :public State {
	State* state;
public:
	StarState(State* state) {
		this->state = state;
	}
	bool isNullable() {
		return true;
	}
	std::vector<int> firstPos() {
		return state->firstPos();
	}
	std::vector<int> lastPos() {
		return state->lastPos();
	}
	void calculateFollowers(std::vector<std::vector<int>>& followersMatrix) {
		state->calculateFollowers(followersMatrix);
		for (int i : lastPos()) {
			for (int j : firstPos()) {
				followersMatrix[i].push_back(j);
			}
		}
	}
};