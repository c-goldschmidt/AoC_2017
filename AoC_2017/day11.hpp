#pragma once
#include "day_factory.hpp"

DAY(Day11)


struct GridCoords {
	int x; int y; int z;
};

class HexGrid {
public:
	HexGrid();
	~HexGrid() = default;

	GridCoords pos;
	void move(string direction);
	int distance();
private:
	map<string, GridCoords> directions;
};

HexGrid::HexGrid() {
	directions["n"] = { 0, 1, -1 };
	directions["ne"] = { 1, 0, -1 };
	directions["nw"] = { -1, 1, 0 };
	directions["s"] = { 0, -1, 1 };
	directions["se"] = { 1, -1, 0 };
	directions["sw"] = { -1, 0, 1 };
	pos = { 0, 0, 0 };
}

void HexGrid::move(string direction) {
	GridCoords delta = directions[direction];

	pos.x += delta.x;
	pos.y += delta.y;
	pos.z += delta.z;
}

int HexGrid::distance() {
	return (abs(pos.x) + abs(pos.y) + abs(pos.z)) / 2;
}

void Day11::part1() {
	HexGrid grid;

	vector<string> directions = split(fileContent[0], ",");
	for (string direction: directions) {
		grid.move(direction);
	}

	printResult(grid.distance());
}

void Day11::part2() {
	HexGrid grid;
	int maxDist = 0;

	vector<string> directions = split(fileContent[0], ",");
	for (string direction : directions) {
		grid.move(direction);
		maxDist = max(maxDist, grid.distance());
	}

	printResult(maxDist);

}