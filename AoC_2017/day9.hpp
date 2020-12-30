#pragma once
#include "day_factory.hpp"

DAY(Day9)

int getGroupScore(string line) {
	bool cancelNext = false;
	bool isGarbage = false;
	int groupLevel = 0;
	int groupScore = 0;

	for (char chr: line) {
		if (cancelNext) {
			cancelNext = false;
		} else if (chr == '!') {
			cancelNext = true;
		} else if (chr == '<') {
			isGarbage = true;
		} else if (isGarbage && chr == '>') {
			isGarbage = false;
		} else if (!isGarbage && chr == '{') {
			groupLevel++;
		} else if (!isGarbage && chr == '}') {
			groupScore += groupLevel;
			groupLevel--;
		}
	}

	return groupScore;
}

int countGarbage(string line) {
	bool cancelNext = false;
	bool isGarbage = false;
	int garbage = 0;

	for (char chr : line) {
		if (cancelNext) {
			cancelNext = false;
		} else if (chr == '!') {
			cancelNext = true;
		} else if (!isGarbage && chr == '<') {
			isGarbage = true;
		} else if (isGarbage && chr == '>') {
			isGarbage = false;
		} else if (isGarbage) {
			garbage++;
		}
	}

	return garbage;
}

void Day9::part1() {
	int totalScore = 0;
	for (string line: fileContent) {
		totalScore += getGroupScore(line);
	}

	printResult(totalScore);
}

void Day9::part2() {
	int totalScore = 0;
	for (string line : fileContent) {
		totalScore += countGarbage(line);
	}

	printResult(totalScore);

}