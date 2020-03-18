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

using namespace std;

enum TypeOfCharacter { star, bar, dot, chara, paranthesisLeft, paranthesisRight };


TypeOfCharacter returnCharState(char x) {
	switch (x) {
	case '*':
		return star;
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

//State* convertStringToRegex(string regex) {
//
//
//}

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
			if (i < regex.size() - 1 && regex[i + 1] == '*') {
				str.append("*");
				i++;
			}
			if (polish != ""){
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
	string polish = convertRegexToPolishForm(regex);

	in.close();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
