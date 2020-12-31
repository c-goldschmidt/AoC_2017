#pragma once
#include "day_factory.hpp"

enum InstType2 { set2, sub, mul2, jnz, jnp};

struct Instruction2 {
	InstType2 type;
	string x;
	string y;
};

class Coprocessor {
public:
	Coprocessor(vector<string>* instructions);
	~Coprocessor() = default;

	void run();
	int mulCount;
	long long getValue(string valueOrRegister);

private:
	map<string, long long> registers;
	vector<Instruction2> instructions;
	uint ptr;

	void runInstruction();
	void set(string x, string y);
	void sub(string x, string y);
	void mul(string x, string y);
	void jnz(string x, string y);
	void jnp(string x, string y);

	bool isPrime(long long value);
};

Coprocessor::Coprocessor(vector<string>* instructions) {
	map<string, InstType2> types;
	types["set"] = InstType2::set2;
	types["sub"] = InstType2::sub;
	types["mul"] = InstType2::mul2;
	types["jnz"] = InstType2::jnz;
	types["jnp"] = InstType2::jnp;

	regex rxMatch("(\\w{3}) (\\w)(?: (-?\\w+))?$");

	for (auto it = instructions->begin(); it != instructions->end(); it++) {
		smatch match;
		regex_match(*it, match, rxMatch);

		Instruction2 inst = { types[match[1]], match[2], match[3] };
		this->instructions.push_back(inst);
	}

	mulCount = 0;
	ptr = 0;
}

void Coprocessor::run() {
	while (ptr < instructions.size()) {
		runInstruction();
		ptr++;
	}
}

void Coprocessor::runInstruction() {
	Instruction2 inst = instructions[ptr];

	switch (inst.type) {
	case InstType2::set2:
		return set(inst.x, inst.y);
	case InstType2::sub:
		return sub(inst.x, inst.y);
	case InstType2::mul2:
		return mul(inst.x, inst.y);
	case InstType2::jnz:
		return jnz(inst.x, inst.y);
	case InstType2::jnp:
		return jnp(inst.x, inst.y);
	}
}

void Coprocessor::set(string x, string y) {
	long long value = getValue(y);
	registers[x] = value;
}

void Coprocessor::sub(string x, string y) {
	long long value = getValue(y);
	registers[x] = getValue(x) - value;
}

void Coprocessor::mul(string x, string y) {
	long long value = getValue(y);
	registers[x] = getValue(x) * value;
	mulCount++;
}

void Coprocessor::jnz(string x, string y) {
	uint value = static_cast<uint>(getValue(y));

	if (getValue(x) != 0) {
		ptr += value - 1;
	}
}

void Coprocessor::jnp(string x, string y) {
	uint value = static_cast<uint>(getValue(y));
	if (!isPrime(getValue(x))) {
		ptr += value - 1;
	}
}

bool Coprocessor::isPrime(long long value) {
	if (value == 0 || value == 1) {
		return false;
	}

	for (long long i = 2; i <= value / 2; ++i) {
		if (value % i == 0) {
			return false;
		}
	}

	return true;
}


long long Coprocessor::getValue(string valueOrRegister) {
	if (regex_match(valueOrRegister, regex("-?\\d+"))) {
		return stoll(valueOrRegister);
	}

	if (auto it = registers.find(valueOrRegister); it != registers.end()) {
		return it->second;
	}
	return 0;
}

DAY(Day23)

void Day23::part1() {
	Coprocessor interpreter(&fileContent);
	interpreter.run();
	printResult(interpreter.mulCount);
}

void Day23::part2() {
	vector<string> instructions(fileContent);
	instructions.insert(instructions.begin(), "set a 1");

	// shortcut around the big loop, which terminates when it finds a prime number
	instructions[9] = "jnp b 17";
	instructions[10] = "jnz 1 17";

	Coprocessor interpreter(&instructions);
	interpreter.run();
	printResult(interpreter.getValue("h"));
}