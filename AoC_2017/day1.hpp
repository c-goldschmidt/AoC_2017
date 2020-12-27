#pragma once
#include "day_factory.hpp"

DAY(Day1)

void Day1::part1() {
	int total = 0;
	string input = this->fileContent[0];

	for (string::size_type i = 0; i < input.size(); i++) {
		string::size_type next = (i + 1) % input.size();

		if (input[next] == input[i]) {
			char nextChar = input[next];
			int value = stoi(&nextChar);
			total += value;
		}
	}

	printResult(total);
}

void Day1::part2() {
	int total = 0;
	string input = this->fileContent[0];

	for (string::size_type i = 0; i < input.size(); i++) {
		string::size_type next = (i + (input.size() / 2)) % input.size();

		if (input[next] == input[i]) {
			char nextChar = input[next];
			int value = stoi(&nextChar);
			total += value;
		}
	}

	printResult(total);
}