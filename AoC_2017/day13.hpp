#pragma once
#include "day_factory.hpp"

DAY(Day13)

class Scanner {
public:
	Scanner(int range = 0);
	~Scanner() = default;

	int range;
	int position;
	void tick();
	void reset();

private:
	int direction;
};

Scanner::Scanner(int range) {
	this->range = range;
	position = 0;
	direction = 1;
}

void Scanner::tick() {
	if (this->range == 0) {
		return;
	}

	if (this->position == this->range - 1) {
		this->direction = -1;
	} else if (this->position == 0) {
		this->direction = 1;
	}

	this->position += this->direction;
}

void Scanner::reset() {
	position = 0;
	direction = 1;
}

class SecurityGrid {
public:
	SecurityGrid(vector<string> input);
	~SecurityGrid() = default;

	void tickScanners();
	void reset();
	int scannerRangeAt(int depth);
	int numLayers;
	map<int, Scanner> scanners;
};

SecurityGrid::SecurityGrid(vector<string> input) {
	regex rxLine("(\\d+): (\\d+)");

	for (string line: input) {
		smatch match;
		regex_match(line, match, rxLine);

		int depth = stoi(match[1]);
		int range = stoi(match[2]);

		scanners[depth] = Scanner(range);
		numLayers = max(numLayers, depth);
	}
}

void SecurityGrid::tickScanners() {
	for(auto& item: scanners) {
		item.second.tick();
	}
}

void SecurityGrid::reset() {
	for (auto& item : scanners) {
		item.second.reset();
	}
}

int SecurityGrid::scannerRangeAt(int depth) {
	if (auto it = scanners.find(depth); it == scanners.end()) {
		return 0;
	}

	if (scanners[depth].position == 0) {
		return scanners[depth].range;
	}
	return 0;
}


void Day13::part1() {
	SecurityGrid grid(fileContent);

	int severity = 0;
	for (int i = 0; i <= grid.numLayers; i++) {
		severity += grid.scannerRangeAt(i) * i;
		grid.tickScanners();
	}
	printResult(severity);
}

bool tryBreaching(SecurityGrid *grid, int delay) {
	for (auto& item : grid->scanners) {
		if ((item.first + delay) % ((item.second.range - 1) * 2) == 0) {
			return false;
		}
	}
	return true;
}

void Day13::part2() {
	SecurityGrid grid(fileContent);

	int delay = 0;
	bool breached = false;
	do {
		delay++;
		breached = tryBreaching(&grid, delay);
	} while (!breached);

	printResult(delay);
}