#pragma once
#include "day_factory.hpp"

DAY(Day19)

class RoutingDiagram {
public:
	RoutingDiagram(vector<string>* input);
	~RoutingDiagram() = default;

	vector<char> run();
	int traveled;
private:
	vector<vector<char>> matrix;
	char at(pair<uint, uint> pos);
	pair<int, int> direction;
	pair<uint, uint> position;
};

RoutingDiagram::RoutingDiagram(vector<string> *input) {
	uint x = 0;
	for (auto it = input->begin(); it != input->end(); it++) {
		vector<char> line;
		for (uint i = 0; i < it->size(); i++) {
			line.push_back(it->at(i));
			if (it == input->begin() && it->at(i) == '|') {
				x = i;
			}
		}
		matrix.push_back(line);
	}

	position = pair(0, x);
	direction = pair(1, 0);
	traveled = 0;
}

char RoutingDiagram::at(pair<uint, uint> pos) {
	if (pos.first >= matrix.size()) {
		return ' ';
	}

	if (pos.second >= matrix[pos.first].size()) {
		return ' ';
	}

	return matrix[pos.first][pos.second];
}

vector<char> RoutingDiagram::run() {
	vector<char> result;

	while (true) {
		char chr = at(position);

		if (chr == ' ') {
			return result;
		} else if (chr == '+') {
			pair dir1(direction.second, direction.first);
			pair dir2(-direction.second, -direction.first);
			pair pos1(position.first + dir1.first, position.second + dir1.second);
			pair pos2(position.first + dir2.first, position.second + dir2.second);

			char chr1 = at(pos1);
			char chr2 = at(pos2);

			if (chr1 != ' ') {
				direction = dir1;
			} else if (chr2 != ' ') {
				direction = dir2;
			}
		} else if(chr != '-' && chr != '|') {
			result.push_back(chr);
		}

		position = pair(position.first + direction.first, position.second + direction.second);
		traveled++;
	}

	return result;
}

void Day19::part1() {
	RoutingDiagram diagram(&fileContent);
	auto result = diagram.run();
	stringstream ss;
	for (char x: result) {
		ss << x;
	}

	printResult(ss.str());
}

void Day19::part2() {
	RoutingDiagram diagram(&fileContent);
	diagram.run();

	printResult(diagram.traveled);
}