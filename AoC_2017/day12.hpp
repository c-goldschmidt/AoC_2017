#pragma once
#include "day_factory.hpp"

DAY(Day12)

map<string, vector<string>> childrenPerNode(vector<string> input) {
	map<string, vector<string>> result;
	regex rxParse("^(\\d+) <-> (.+)$");

	for (string line: input) {
		smatch match;
		regex_match(line, match, rxParse);
		result[match[1]] = split(match[2], ", ");
	}
	return result;
}

int countChildren(map<string, vector<string>> *children, string parent, set<string> *found) {
	if (auto it = found->find(parent); it != found->end()) {
		return 0;
	}
	found->insert(parent);

	int count = 1;
	for (string child: children->at(parent)) {
		count += countChildren(children, child, found);
	}
	return count;
}

void Day12::part1() {
	auto children = childrenPerNode(fileContent);
	set<string> found;

	int childCount = countChildren(&children, "0", &found);
	printResult(childCount);
}

void Day12::part2() {
	auto children = childrenPerNode(fileContent);
	set<string> found;

	int groupCount = 0;
	for (auto item: children) {
		if (countChildren(&children, item.first, &found) > 0) {
			// didn't encounter this node before, therefore it is not in found,
			// which means that there was no group before that contained this node.
			groupCount++;
		}
	}

	printResult(groupCount);
}