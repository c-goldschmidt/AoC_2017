#pragma once
#pragma once
#include "day_factory.hpp"

DAY(Day3)


class ValueMap {
public:
	~ValueMap() = default;
	ValueMap() = default;

	int setValue(int y, int x);
private:
	int getValue(int y, int x);
	map<int, map<int, int>> values;
};

int ValueMap::setValue(int y, int x) {
	int value = getValue(y, x + 1) + getValue(y, x - 1)
		+ getValue(y + 1, x) + getValue(y + 1, x + 1) + getValue(y + 1, x - 1)
		+ getValue(y - 1, x) + getValue(y - 1, x + 1) + getValue(y - 1, x - 1);

	if (value == 0) {
		// first insert ever
		value = 1;
	}

	if (auto row = values.find(y); row == values.end()) {
		map<int, int> rowData;
		values[y] = rowData;
	}
	values[y][x] = value;
	return value;
}

int ValueMap::getValue(int y, int x) {
	if (auto row = values.find(y); row != values.end()) {
		if (auto col = values[y].find(x); col != values[y].end()) {
			return values[y][x];
		}
	}

	return 0;
}

void Day3::part1() {
	int direction[2] = { 0, 1 };
	int len = 1;

	int y = 0;
	int x = 0;
	int currLen = 0;
	int numPoints = atoi(fileContent[0].c_str());

	for (int i = 1; i < numPoints; i++) {
		y += direction[0];
		x += direction[1];

		currLen++;
		if (currLen == len) {
			currLen = 0;
			int tmp = direction[0];
			direction[0] = -direction[1];
			direction[1] = tmp;

			if (direction[0] == 0) {
				len++;
			}
		}
	}
	
	int dist = abs(y) + abs(x);
	printResult(dist);
}

void Day3::part2() {
	ValueMap data;

	int direction[2] = { 0, 1 };
	int len = 1;

	int y = 0;
	int x = 0;
	int currLen = 0;

	int searchValue = atoi(fileContent[0].c_str());
	int currentValue = 0;

	while (currentValue < searchValue) {
		currentValue = data.setValue(x, y);

		y += direction[0];
		x += direction[1];

		currLen++;
		if (currLen == len) {
			currLen = 0;
			int tmp = direction[0];
			direction[0] = -direction[1];
			direction[1] = tmp;

			if (direction[0] == 0) {
				len++;
			}
		}
	}

	printResult(currentValue);
}