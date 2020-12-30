#pragma once
#include "day_factory.hpp"

DAY(Day15)

class Generator {
public:
	Generator(ulong start, ulong factor);
	~Generator() = default;

	ulong start;
	ulong factor;

	ulong next(ulong mod = 0);

private:
	ulong prev;
};

Generator::Generator(ulong start, ulong factor) {
	this->start = start;
	this->factor = factor;
	prev = start;
}

ulong Generator::next(ulong mod) {
	bool matches = false;
	while (!matches) {
		ulong next = (prev * factor) % 2147483647;
		prev = next;
		matches = mod == 0 || next % mod == 0;
	}

	return prev;
}

ulong getStartValue(string line) {
	regex rxMatch("Generator (?:A|B) starts with (\\d+)");
	smatch match;
	regex_match(line, match, rxMatch);
	return stoi(match[1]);
}

int countMatches(ulong start1, ulong start2, int tries, ulong mod1 = 0, ulong mod2 = 0) {
	Generator gen1(start1, 16807);
	Generator gen2(start2, 48271);
	ulong mask = 65535; // 2^16 - 1
	int matches = 0;

	for (int i = 0; i < tries; i++) {
		ulong val1 = gen1.next(mod1);
		ulong val2 = gen2.next(mod2);

		if ((val1 & mask) == (val2 & mask)) {
			matches++;
		}
	}

	return matches;
}

void Day15::part1() {
	ulong start1 = getStartValue(fileContent[0]);
	ulong start2 = getStartValue(fileContent[1]);
	printResult(countMatches(start1, start2, 40000000));
}

void Day15::part2() {
	ulong start1 = getStartValue(fileContent[0]);
	ulong start2 = getStartValue(fileContent[1]);
	printResult(countMatches(start1, start2, 5000000, 4, 8));
}