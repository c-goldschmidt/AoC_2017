#pragma once
#include "day_factory.hpp"
#include <queue>

DAY(Day18)

enum InstType {snd, set, add, mul, mod, rcv, jgz};

struct Instruction {
	InstType type;
	string x;
	string y;
};

class DuetInterpreter {
public:
	DuetInterpreter(vector<string> *instructions, long long p = 0);
	~DuetInterpreter() = default;

	queue<long long> queue;
	DuetInterpreter* other;

	void run();
	bool tick();
	long long lastRecovered;
	uint sendCount;
private:
	uint ptr;
	long long lastPlayed;
	long long progId;
	map<string, long long> registers;
	vector<Instruction> instructions;

	long long getValue(string valueOrRegister);
	bool runInstruction();

	bool snd(string x);
	bool set(string x, string y);
	bool add(string x, string y);
	bool mul(string x, string y);
	bool mod(string x, string y);
	bool rcv(string x);
	bool jgz(string x, string y);
};

DuetInterpreter::DuetInterpreter(vector<string>* instructions, long long p) {
	map<string, InstType> types;
	types["snd"] = InstType::snd;
	types["set"] = InstType::set;
	types["add"] = InstType::add;
	types["mul"] = InstType::mul;
	types["mod"] = InstType::mod;
	types["rcv"] = InstType::rcv;
	types["jgz"] = InstType::jgz;

	regex rxMatch("(\\w{3}) (\\w)(?: (-?\\w+))?$");

	for (auto it = instructions->begin(); it != instructions->end(); it++) {
		smatch match;
		regex_match(*it, match, rxMatch);

		Instruction inst = { types[match[1]], match[2], match[3] };
		this->instructions.push_back(inst);
	}

	ptr = 0;
	lastRecovered = 0;
	lastPlayed = 0;
	sendCount = 0;
	progId = p;
	registers["p"] = p;
	other = nullptr;
}

void DuetInterpreter::run() {
	while (ptr < instructions.size()) {
		if (runInstruction()) {
			break;
		}
		ptr++;
	}
}

bool DuetInterpreter::tick() {
	if (ptr >= instructions.size()) {
		return true;
	}

	if (runInstruction()) {
		return true;
	}
	ptr++;
	return false;
}

long long DuetInterpreter::getValue(string valueOrRegister) {
	if (regex_match(valueOrRegister, regex("-?\\d+"))) {
		return stoll(valueOrRegister);
	}

	if (auto it = registers.find(valueOrRegister); it != registers.end()) {
		return it->second;
	}
	return 0;
}

bool DuetInterpreter::runInstruction() {
	Instruction inst = instructions[ptr];

	// print(progId << " => " << inst.type << ", " << inst.x << ", " << inst.y );

	switch (inst.type) {
	case InstType::snd:
		return snd(inst.x);
	case InstType::set:
		return set(inst.x, inst.y);
	case InstType::add:
		return add(inst.x, inst.y);
	case InstType::mul:
		return mul(inst.x, inst.y);
	case InstType::mod:
		return mod(inst.x, inst.y);
	case InstType::rcv:
		return rcv(inst.x);
	case InstType::jgz:
		return jgz(inst.x, inst.y);
	default:
		return false;
	}
}

bool DuetInterpreter::snd(string x) {
	if (other == nullptr) {
		lastPlayed = getValue(x);
	} else {
		other->queue.push(getValue(x));
		sendCount++;
	}
	return false;
}

bool DuetInterpreter::set(string x, string y) {
	long long value = getValue(y);
	registers[x] = value;
	return false;
}

bool DuetInterpreter::add(string x, string y) {
	long long value = getValue(y);
	registers[x] = getValue(x) + value;
	return false;
}

bool DuetInterpreter::mul(string x, string y) {
	long long value = getValue(y);
	registers[x] = getValue(x) * value;
	return false;
}

bool DuetInterpreter::mod(string x, string y) {
	long long value = getValue(y);
	registers[x] = getValue(x) % value;
	return false;
}

bool DuetInterpreter::rcv(string x) {
	if (other == nullptr) {
		long long value = getValue(x);
		if (value != 0) {
			lastRecovered = lastPlayed;
			return true;
		}
		return false;
	} else {
		if (queue.empty()) {
			return true;
		}
		registers[x] = queue.front();
		queue.pop();
		return false;
	}
}

bool DuetInterpreter::jgz(string x, string y) {
	uint value = static_cast<uint>(getValue(y));
	if (getValue(x) > 0) {
		ptr += value - 1;
	}
	return false;
}

void Day18::part1() {
	DuetInterpreter interpreter(&fileContent);
	interpreter.run();
	printResult(interpreter.lastRecovered);
}

void Day18::part2() {
	bool aDoneOrWaiting = false;
	bool bDoneOrWaiting = false;

	DuetInterpreter interpreterA(&fileContent, 0);
	DuetInterpreter interpreterB(&fileContent, 1);
	interpreterA.other = &interpreterB;
	interpreterB.other = &interpreterA;

	while (!aDoneOrWaiting || !bDoneOrWaiting) {
		aDoneOrWaiting = interpreterA.tick();
		bDoneOrWaiting = interpreterB.tick();
	}

	printResult(interpreterB.sendCount);
}