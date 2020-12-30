#pragma once
#include <bitset>
#include "day_factory.hpp"
#include "day10.hpp"

DAY(Day14)

vector<bool> strToBool(string input) {
	vector<bool> result;

	for (auto chr: input) {
		stringstream ss;
		ss << hex << "0x" << chr;

		uint n;
		ss >> n;

		for (auto bit: bitset<4>(n).to_string()) {
			result.push_back(bit == '1');
		}
	}

	return result;
}

vector<vector<bool>> generateContent(string key) {
	vector<vector<bool>> result;
	for (int i = 0; i < 128; i++) {
		stringstream ss;
		ss << key << "-" << i;

		result.push_back(strToBool(knotHash(ss.str())));
	}
	return result;
}

int countTrue(vector<vector<bool>> input) {
	int total = 0;
	for (auto row: input) {
		for (auto col : row) {
			total += col ? 1 : 0;
		}
	}
	return total;
}

int getRegionSize(vector<vector<bool>>* input, uint x, uint y, set<string>* found) {
	if (!input->at(x).at(y)) {
		return 0;
	}

	stringstream ss;
	ss << x << "," << y;
	string coords = ss.str();

	if (auto it = found->find(coords); it != found->end()) {
		return 0;
	}
	found->insert(coords);

	int regionSize = 1;
	if (x < input->size() - 1) {
		regionSize += getRegionSize(input, x + 1, y, found);
	}
	if (y < input->size() - 1) {
		regionSize += getRegionSize(input, x, y + 1, found);
	}
	if (x > 0) {
		regionSize += getRegionSize(input, x - 1, y, found);
	}
	if (y > 0) {
		regionSize += getRegionSize(input, x, y - 1, found);
	}

	return regionSize;
}

void Day14::part1() {
	auto content = generateContent(fileContent[0]);
	printResult(countTrue(content));
}

void Day14::part2() {
	auto content = generateContent(fileContent[0]);
	set<string> found;
	int regions = 0;
	for (uint i = 0; i < content.size(); i++) {
		for (uint j = 0; j < content.size(); j++) {
			if (getRegionSize(&content, i, j, &found) > 0) {
				// same as in puzzle 12, if item was already in a region, the size is 0
				regions++;
			}
		}
	}
	printResult(regions);
}