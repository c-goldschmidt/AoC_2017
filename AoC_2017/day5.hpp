#pragma once
#include "day_factory.hpp"

DAY(Day5)

vector<int> toIntVector(vector<string> input) {
	vector<int> output;
	for (string item: input) {
		output.push_back(atoi(item.c_str()));
	}
	return output;
}

void Day5::part1() {
	vector<int> items = toIntVector(fileContent);
	uint index = 0;
	uint steps = 0;
	while (index < fileContent.size()) {
		int jmp = items[index];
		items[index]++;
		index += jmp;
		steps += 1;
	}
	printResult(steps);
}

void Day5::part2() {
	vector<int> items = toIntVector(fileContent);
	uint index = 0;
	uint steps = 0;
	while (index < fileContent.size()) {
		int jmp = items[index];
		items[index] += items[index] >= 3 ? -1 : 1;
		index += jmp;
		steps += 1;
	}

	printResult(steps);
}