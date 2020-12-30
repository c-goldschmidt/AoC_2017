#pragma once
#include "day_factory.hpp"
#include <iomanip>

DAY(Day10)


vector<int> makeVector() {
	vector<int> result;
	for (int i = 0; i < 256; i++) {
		result.push_back(i);
	}
	return result;
}

vector<int> reverseSection(vector<int> vec, uint start, uint len) {
	vector<int> out(vec);

	for (uint i = 0; i < len; i++) {
		out[(start + i) % vec.size()] = vec[((start + (len - 1)) - i) % vec.size()];
	}
	return out;
}

vector<int> runRound(vector<int> vec, vector<uint> lengths, uint *skip, uint *pos) {
	for (int len: lengths) {
		vec = reverseSection(vec, *pos, len);
		*pos = (*pos + len + *skip) % vec.size();
		*skip = *skip + 1;
	}
	return vec;
}

vector<uint> lengthsFromString(string input) {
	vector<uint> result;
	for (char chr: input) {
		result.push_back(chr);
	}

	// magic chars from challenge
	result.push_back(17);
	result.push_back(31);
	result.push_back(73);
	result.push_back(47);
	result.push_back(23);

	return result;
}

vector<int> densify(vector<int> vec) {
	vector<int> result;

	for (uint i = 0; i < vec.size(); i += 16) {
		int value = vec[i];
		for (uint j = 1; j < 16; j++) {
			value = value ^ vec[i + j];
		}
		result.push_back(value);
	}

	return result;
}

string knotHash(string input) {
	vector<int> vec = makeVector();
	vector<uint> lengths = lengthsFromString(input);

	uint skip = 0;
	uint pos = 0;

	for (int round = 0; round < 64; round++) {
		vec = runRound(vec, lengths, &skip, &pos);
	}
	vector<int> digest = densify(vec);
	string hexString;
	for (auto x : digest) {
		ostringstream oss;
		oss << hex << std::setw(2) << std::setfill('0') << (unsigned)x;
		hexString += oss.str();
	}

	return hexString;
}

void Day10::part1() {
	vector<int> vec = makeVector();
	uint skip = 0;
	uint pos = 0;

	vector<string> lengths = split(fileContent[0], ",");
	vector<uint> intLengths;
	for (string len: lengths) {
		intLengths.push_back(stoi(len));
	}

	vec = runRound(vec, intLengths, &skip, &pos);
	print("skip=" << skip << ", pos=" << pos);
	printResult(vec[0] * vec[1]);
}

void Day10::part2() {
	printResult(knotHash(fileContent[0]));
}