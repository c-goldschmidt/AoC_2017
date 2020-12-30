#pragma once
#include "day_factory.hpp"

DAY(Day8)

int valueOr0(map<string, int> *registers, string key) {
	if (auto it = registers->find(key); it == registers->end()) {
		return 0;
	}
	return registers->at(key);
}

void runInstruction(string inst, map<string, int> *registers) {
	regex rxLine("(\\w+) (inc|dec) (-?\\d+) if (\\w+) ([!=><]+) (-?\\d+)");

	smatch match;
	regex_match(inst, match, rxLine);

	string target = match[1];
	int mod = match[2] == "inc" ? 1 : -1;
	int value = stoi(match[3]) * mod;
	string conditionRegister = match[4];
	string operation = match[5];
	int conditionValue = stoi(match[6]);
	int registerValue = valueOr0(registers, conditionRegister);
	int targetValue = valueOr0(registers, target);

	if (operation == "<=" && registerValue <= conditionValue) {
		targetValue += value;
	} else if (operation == ">=" && registerValue >= conditionValue) {
		targetValue += value;
	} else if (operation == "==" && registerValue == conditionValue) {
		targetValue += value;
	} else if (operation == "!=" && registerValue != conditionValue) {
		targetValue += value;
	} else if (operation == ">" && registerValue > conditionValue) {
		targetValue += value;
	} else if (operation == "<" && registerValue < conditionValue) {
		targetValue += value;
	}

	auto it = registers->find(target);
	if (it == registers->end()) {
		registers->insert(pair(target, targetValue));
	} else {
		it->second = targetValue;
	}
	
}

int getMax(map<string, int>* registers) {
	int maxVal = 0;
	for (auto item: *registers) {
		maxVal = max(item.second, maxVal);
	}
	return maxVal;
}

void Day8::part1() {
	map<string, int> registers;

	for (string line: fileContent) {
		runInstruction(line, &registers);
	}

	printResult(getMax(&registers));
}

void Day8::part2() {
	map<string, int> registers;
	int totalMax = 0;

	for (string line : fileContent) {
		runInstruction(line, &registers);
		totalMax = max(getMax(&registers), totalMax);
	}

	printResult(totalMax);
}