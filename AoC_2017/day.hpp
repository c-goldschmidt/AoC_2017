#pragma once
#include "includes.h"
#include "utils.hpp"

class Day {

public:
	Day() = default;
	virtual ~Day() = default;

	bool readFile(string fileName);

	virtual void part1() = 0;
	virtual void part2() = 0;

protected:
	vector<string> fileContent;
};

bool Day::readFile(string fileName) {
	ifstream inFile;
	stringstream strStream;

	inFile.open(fileName);

	if (!inFile.good()) {
		cout << "error reading file: " << fileName << endl;
		return false;
	}

	strStream << inFile.rdbuf();

	this->fileContent = split(strStream.str(), "\\r?\\n");
	return true;
}
