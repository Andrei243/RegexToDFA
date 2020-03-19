// Proiect TC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include "DotState.h"
#include "LambdaState.h"
#include "NodeState.h"
#include "OrState.h"
#include "StarState.h"
#include <map>
#include <set>
#include <queue>

using namespace std;

enum TypeOfCharacter { star, bar, dot, chara, paranthesisLeft, paranthesisRight };
std::vector<char> letterOnPosition;
std::set<char> letters;


TypeOfCharacter returnCharState(char x) {
	switch (x) {
	case '*':
		return star;
	case '.':
		return dot;
	case '|':
		return bar;
	case '(':
		return paranthesisLeft;
	case ')':
		return paranthesisRight;
	default:
		return chara;

	}

}


State* convertRegexToTree(string regex) {
	std::vector<State*> states;
	for (int i = 0; i < regex.size(); i++) {
		char character = regex[i];
		TypeOfCharacter type = returnCharState(character);
		switch (type) {
		case chara: {
			NodeState* state = new NodeState(letterOnPosition.size(), character);
			letters.insert(character);
			letterOnPosition.push_back(character);
			states.push_back(state);
			break;
		}
		case star: {
			State* lastState = states[states.size() - 1];
			states.pop_back();
			StarState* newState = new StarState(lastState);
			states.push_back(newState);
			break;
		}
		case dot: {
			State* leftState = states[states.size() - 2];
			State* rightState = states[states.size() - 1];
			states.pop_back();
			states.pop_back();
			DotState* newState = new DotState(leftState, rightState);
			states.push_back(newState);
			break;
		}
		case bar: {
			State* leftState = states[states.size() - 2];
			State* rightState = states[states.size() - 1];
			states.pop_back();
			states.pop_back();
			OrState* newState = new OrState(leftState, rightState);
			states.push_back(newState);
			break;
		}
		}

	}
	return states[0];

}

int findRightParanthesis(string characters, int offset) {
	int leftParanthesisFound = 0;
	for (int i = offset + 1; i < (int)characters.size(); i++) {
		if (characters[i] == '(') {
			leftParanthesisFound++;
		}
		else if (characters[i] == ')') {
			if (leftParanthesisFound == 0) {
				return i - 1;
			}
			else leftParanthesisFound--;

		}
	}
	return characters.size() - 1;
}

string convertRegexToPolishForm(string regex) {
	string polish = "";
	for (int i = 0; i < regex.size(); i++) {
		char character = regex[i];
		TypeOfCharacter type = returnCharState(character);
		switch (type) {
		case star: {
			polish.append("*");
			break; }
		case chara: {
			string str = "";
			str += character;
			if (polish != "") {
				str += ".";
			}
			polish.append(str);
			break; }
		case bar: {
			string rightSide;
			rightSide.assign(regex.begin() + i + 1, regex.begin() + findRightParanthesis(regex, i) + 1);
			polish.append(convertRegexToPolishForm(rightSide));
			polish.append("|");
			i += rightSide.size();
			break; }
		case paranthesisLeft: {
			string interior;
			interior.assign(regex.begin() + i + 1, regex.begin() + findRightParanthesis(regex, i + 1) + 1);
			string str;
			str.append(convertRegexToPolishForm(interior));
			i += interior.size() + 2;
			if (i < regex.size() - 1 && regex[i] == '*') {
				str.append("*");
			}
			if (polish != "") {
				str.append(".");
			}
			polish.append(str);
			break; }
		case paranthesisRight: {
			i++;
			break; }

		}

	}
	return polish;
}

int main()
{

	ifstream in("regex.txt", ifstream::in);
	string regex;
	in >> regex;
	regex += "#";
	string polish = convertRegexToPolishForm(regex);

	State* state = convertRegexToTree(polish);
	letters.erase('#');
	in.close();

	vector<vector<int>> vec(letterOnPosition.size(), vector<int>());

	state->calculateFollowers(vec);


	map<int, map<char, int>> automata;
	map<set<int>, int> statesToState;
	queue<set<int>> currentStates;


	vector<int> firstStatesVector = state->firstPos();
	set<int> firstState = set<int>(firstStatesVector.begin(), firstStatesVector.end());

	int currentState = 0;
	statesToState.insert(pair<set<int>, int>(firstState, currentState));
	currentStates.push(firstState);
	currentState++;


	while (!currentStates.empty()) {
		set<int> positions = currentStates.front();
		currentStates.pop();
		int position = statesToState[positions];


		for (char c : letters) {
			set<int> nextState;
			for (int position : positions) {
				if (letterOnPosition[position] == c) {
					vector<int>followPos = vec[position];
					for (int follow : followPos) {
						nextState.insert(follow);
					}

				}

			}
			if (statesToState.find(nextState) == statesToState.end()) {
				statesToState.insert(pair<set<int>, int>(nextState, currentState));
				automata[position].insert(pair<char, int>(c, currentState));
				currentState++;
				currentStates.push(nextState);
			}
			else {
				automata[position][c] = statesToState[nextState];
			}
		}


	}

	cout << "Literele alfabetului sunt: ";
	for (char c : letters) {
		cout << c << " ";
	}
	cout << '\n';
	cout << "Starile automatului sunt: ";
	for (pair<set<int>, int> c : statesToState) {
		cout << "q" << c.second << "  ";
	}
	cout << "cu statea initiala q0 si starile finale: ";
	for (pair<set<int>, int> c : statesToState) {
		if (c.first.find(letterOnPosition.size() - 1) != c.first.end()) {
			cout << "q" << c.second << "  ";
		}
	}
	cout << '\n' << "Tranzitiile sunt urmatoarele: \n";

	for (pair<int, map<char, int>> translatie : automata) {
		for (pair<char, int> rezultant : translatie.second) {
			cout << "q" << translatie.first << " -" << rezultant.first << "> q" << rezultant.second << '\n';
		}

	}

	return 0;

}

