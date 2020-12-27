#pragma once
#include "day_factory.hpp"
#include "utils.hpp"

DAY(Day2)

void Day2::part1() {
	int chksum = 0;

	for (string line : this->fileContent) {
		auto lineSplit = split(line, "\\s+");
		int minVal = INT_MAX;
		int maxVal = INT_MIN;
		for (auto item: lineSplit) {
			minVal = min(minVal, atoi(item.c_str()));
			maxVal = max(maxVal, atoi(item.c_str()));
		}
		chksum += maxVal - minVal;
	}

	printResult(chksum);
}

int findDivisor(vector<string> lineSplit) {
	for (auto item : lineSplit) {
		for (auto other : lineSplit) {
			if (item == other) {
				continue;
			}
			int a = atoi(item.c_str());
			int b = atoi(other.c_str());

			if (a % b == 0) {
				return a / b;
			}
		}
	}
	return 0;
}

void Day2::part2() {
	int chksum = 0;

	for (string line : this->fileContent) {
		auto lineSplit = split(line, "\\s+");
		chksum += findDivisor(lineSplit);
	}

	printResult(chksum);
}
