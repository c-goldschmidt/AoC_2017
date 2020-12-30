#pragma once
#include "day_factory.hpp"

DAY(Day17)

void splinlock(vector<int> *result, int steps, int value, int *pos) {
	*pos = (*pos + steps) % result->size() + 1;
	result->insert(result->begin() + *pos, value);
}

void Day17::part1() {
	vector<int> result = {0};
	int steps = stoi(fileContent[0]);
	int pos = 0;
	for (int i = 1; i < 2018; i++) {
		splinlock(&result, steps, i, &pos);
	}

	printResult(result[pos + 1]);
}

void Day17::part2() {
	// actually simulating this takes way too long
	int result = 0;
	int steps = stoi(fileContent[0]);
	int pos = 0;

	for (int i = 1; i < 50000000; i++) {
		pos = (pos + steps) % i + 1;
		if (pos == 1) {
			result = i;
		}
	}

	printResult(result);
}