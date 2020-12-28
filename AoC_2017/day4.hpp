#pragma once
#include <set>
#include "day_factory.hpp"

DAY(Day4)

bool noDuplicates(string input) {
	set<string> wordSet;
	for (string word : split(input, " ")) {
		if (auto it = wordSet.find(word); it != wordSet.end()) {
			return false;
		}
		wordSet.insert(word);
	}
	return true;
}

bool isAnagram(string word1, string word2) {
	if (word1.length() != word2.length()) {
		return false;
	}

	map<char, int> charSet;
	for (char chr: word1) {
		if (auto it = charSet.find(chr); it == charSet.end()) {
			charSet[chr] = 0;
		}

		charSet[chr]++;
	}

	for (char chr: word2) {
		if (auto it = charSet.find(chr); it == charSet.end()) {
			return false;
		}

		if (charSet[chr] == 0) {
			return 0;
		}

		charSet[chr]--;
	}

	return true;
}

bool noAnagrams(string input) {
	vector<string> words = split(input, " ");
	for (uint i = 0; i < words.size(); i++) {
		for (uint j = 0; j < words.size(); j++) {
			if (i == j) {
				continue;
			}
			if (isAnagram(words[i], words[j])) {
				return false;
			}
		}
	}
	return true;

}

void Day4::part1() {
	int valid = 0;
	for (string line: fileContent) {
		if (noDuplicates(line)) {
			valid++;
		}
	}
	printResult(valid);
}

void Day4::part2() {
	int valid = 0;
	for (string line : fileContent) {
		if (noAnagrams(line)) {
			valid++;
		}
	}
	printResult(valid);
}