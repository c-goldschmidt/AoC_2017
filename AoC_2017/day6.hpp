#pragma once
#include "day_factory.hpp"

DAY(Day6)

class MemBanks {
public:
	MemBanks() = default;
	~MemBanks() = default;

	void fill(string input);
	uint redistribute(void);
private:
	set<uint> states;
	vector<int> banks;
	uint hash();
};

uint MemBanks::hash() {
	uint seed = banks.size();
	for (auto& i : banks) {
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

uint MemBanks::redistribute() {
	int vecMax = 0;
	uint index = 0;

	for (uint i = 0; i < banks.size(); i++) {
		if (banks[i] > vecMax) {
			vecMax = banks[i];
			index = i;
		}
	}

	banks[index] = 0;
	for (int i = 1; i <= vecMax; i++) {
		banks[(index + i) % banks.size()] += 1;
	}

	uint hashed = hash();
	auto row = states.find(hashed);
	states.insert(hashed);
	return row != states.end() ? hashed : 0;
}

void MemBanks::fill(string input) {
	vector<string> bankContent = split(input, "\\s+");
	for (string item: bankContent) {
		banks.push_back(atoi(item.c_str()));
	}
}


void Day6::part1() {
	MemBanks banks;
	banks.fill(fileContent[0]);

	uint stateFound = 0;
	int tries = 0;

	while (stateFound == 0) {
		tries++;
		stateFound = banks.redistribute();
	}

	printResult(tries);
}

void Day6::part2() {
	MemBanks banks;
	banks.fill(fileContent[0]);

	uint stateFound = 0;
	while (stateFound == 0) {
		stateFound = banks.redistribute();
	}

	uint foundAgain = 0;
	int tries = 0;
	while (foundAgain != stateFound) {
		tries++;
		foundAgain = banks.redistribute();
	}

	printResult(tries);

}