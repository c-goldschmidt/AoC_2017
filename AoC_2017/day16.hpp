#pragma once
#include "day_factory.hpp"

DAY(Day16)

vector<char> getDancers() {
	vector<char> result;

	// a though p
	for (char i = 97; i <= 112; i++) {
		result.push_back(i);
	}
	return result;
}

void spin(string item, vector<char> *dancers) {
	smatch match;
	regex_match(item, match, regex("s(\\d+)"));

	if (match[0].length() == 0) {
		return;
	}

	int num = stoi(match[1]);

	for (int i = 0; i < num; i++) {
		char d = dancers->at(dancers->size() - 1);
		dancers->pop_back();
		dancers->insert(dancers->begin(), d);
	}
}

void swap(vector<char>* dancers, uint a, uint b) {
	char atB = dancers->at(b);
	(*dancers)[b] = dancers->at(a);
	(*dancers)[a] = atB;
}

void exchange(string item, vector<char> *dancers) {
	smatch match;
	regex_match(item, match, regex("x(\\d+)/(\\d+)"));

	if (match[0].length() == 0) {
		return;
	}

	uint a = stoi(match[1]);
	uint b = stoi(match[2]);
	swap(dancers, a, b);
}

void partner(string item, vector<char>* dancers) {
	smatch match;
	regex_match(item, match, regex("p(\\w)/(\\w)"));

	if (match[0].length() == 0) {
		return;
	}

	uint a = find(dancers->begin(), dancers->end(), match[1].str()[0]) - dancers->begin();
	uint b = find(dancers->begin(), dancers->end(), match[2].str()[0]) - dancers->begin();
	swap(dancers, a, b);
}

void runMoves(vector<string> moves, vector<char>* dancers) {
	for (string move : moves) {
		if (move[0] == 's') {
			spin(move, dancers);
		}
		if (move[0] == 'x') {
			exchange(move, dancers);
		}
		if (move[0] == 'p') {
			partner(move, dancers);
		}
	}
}

string toString(vector<char> dancers) {
	stringstream ss;
	for (char item : dancers) {
		ss << item;
	}
	return ss.str();
}

void Day16::part1() {
	auto dancers = getDancers();
	auto moves = split(fileContent[0], ",");
	runMoves(moves, &dancers);
	printResult(toString(dancers));

}

void Day16::part2() {
	auto dancers = getDancers();
	auto moves = split(fileContent[0], ",");

	vector<string> found;

	int repeatsAt = 0;
	while (true) {
		runMoves(moves, &dancers);
		string asStr = toString(dancers);

		if (found.size() > 0 && found[0] == asStr) {
			break;
		}

		found.push_back(asStr);
		repeatsAt++;
	}

	// offset after 1B repititions (-1 for the initial dance)
	int offset = 999999999 % repeatsAt;
	printResult(found[offset]);
}
