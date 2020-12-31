#pragma once
#include "day_factory.hpp"

struct Tape {
	map<int, ushort> values;
	int position = 0;

	ushort current() {
		return get(position);
	}

	void setCurrent(ushort value) {
		values[position] = value;
	}

	int sum() {
		int result = 0;
		for (auto item: values) {
			if (item.second == 1) {
				result++;
			}
		}
		return result;
	}

	void set(int index, ushort value) {
		values[index] = value;
	}

	ushort get(int index) {
		if (auto it = values.find(index); it == values.end()) {
			return 0;
		}
		return values[index];
	}
};

struct State {
	// current is 0
	int write0;
	int move0;
	string next0;

	// current is 1
	int write1;
	int move1;
	string next1;
};

DAY(Day25)

class StateMachine {
public:
	StateMachine(vector<string>* input);
	~StateMachine() = default;

	int run();
private:
	map<string, State> states;
	string currentState;
	Tape tape;
	int stepsRemain;
	int parseState(vector<string>* input, uint offset);
	string parseStateName(string input);
	ushort parseValue(string input);
	int parseMove(string input);
};

StateMachine::StateMachine(vector<string>* input) {
	regex rxSteps("checksum after (\\d+) steps");

	// first line: start state (probably A)
	currentState = parseStateName(input->at(0));
	smatch match;

	// second line: steps to simulate
	regex_search(input->at(1), match, rxSteps);
	stepsRemain = stoi(match[1]);
	
	uint offset = 2;
	while (offset < input->size()) {
		offset = parseState(input, offset);
	}
}

string StateMachine::parseStateName(string input) {
	regex rxState("state ([A-F])");
	smatch match;
	regex_search(input, match, rxState);
	return match[1];
}

int StateMachine::parseMove(string input) {
	regex rxMove("to the (left|right)");
	smatch match;
	regex_search(input, match, rxMove);
	return match[1] == "right" ? 1 : -1;
}

ushort StateMachine::parseValue(string input) {
	regex rxWrite("the value ([01])");
	smatch match;
	regex_search(input, match, rxWrite);
	return static_cast<ushort>(stoi(match[1]));
}

int StateMachine::parseState(vector<string>* input, uint offset) {
	// offset + 0: empty line
	string name = parseStateName(input->at(offset + 1));

	// offset + 2: "If the current value is 0"
	State result = {};
	result.write0 = parseValue(input->at(offset + 3));
	result.move0 = parseMove(input->at(offset + 4));
	result.next0 = parseStateName(input->at(offset + 5));

	// offset + 6: "If the current value is 1"
	result.write1 = parseValue(input->at(offset + 7));
	result.move1 = parseMove(input->at(offset + 8));
	result.next1 = parseStateName(input->at(offset + 9));

	states[name] = result;
	return offset + 10;
}

int StateMachine::run() {
	for (int i = 0; i < stepsRemain; i++) {
		ushort value = tape.current();
		State state = states[currentState];

		if (value == 0) {
			tape.setCurrent(state.write0);
			tape.position += state.move0;
			currentState = state.next0;
		} else {
			tape.setCurrent(state.write1);
			tape.position += state.move1;
			currentState = state.next1;
		}
	}
	return tape.sum();
}

void Day25::part1() {
	StateMachine sm(&fileContent);
	int value = sm.run();
	printResult(value);
}

void Day25::part2() {
	printResult("Happy holidays!");
}