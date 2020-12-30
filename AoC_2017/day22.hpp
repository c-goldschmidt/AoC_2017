#pragma once
#include "day_factory.hpp"

enum Flag {clean, weak, infected, flagged};

DAY(Day22)

class CarrierGrid {
public:
	CarrierGrid(vector<string> *input);
	~CarrierGrid() = default;

	void tick();
	void tickMulti();
	int infectCount;

private:
	Point2D direction;
	Point2D position;
	map<string, Flag> grid;
	map<string, Point2D> gridCoords;

	Flag at(Point2D *pos);
};

CarrierGrid::CarrierGrid(vector<string>* input) {
	infectCount = 0;

	for (uint i = 0; i < input->size(); i++) {
		string str = input->at(i);
		for (uint j = 0; j < str.length(); j++) {
			Point2D coords = { i, j };
			gridCoords.insert(pair(coords.str(), coords));
			grid.insert(pair(coords.str(), str[j] == '#' ? infected : clean));
		}
	}

	direction = {-1, 0};
	position = { input->size() / 2, input->size() / 2 };
}

Flag CarrierGrid::at(Point2D* pos) {
	if (auto it = grid.find(pos->str()); it != grid.end()) {
		return it->second;
	}
	return clean;
}

void CarrierGrid::tick() {
	Flag cellFlag = at(&position);

	if (cellFlag == infected) {
		Point2D newDirection = {direction.x, -direction.y};
		direction = newDirection;
		grid[position.str()] = clean;
	} else {
		Point2D newDirection = {-direction.x, direction.y };
		direction = newDirection;
		grid[position.str()] = infected;
		infectCount++;
	}

	position.add(&direction);
}

void CarrierGrid::tickMulti() {
	Flag cellFlag = at(&position);

	switch (cellFlag) {
	case clean:
		direction = { -this->direction.x, this->direction.y };
		grid[position.str()] = weak;
		break;
	case weak:
		grid[position.str()] = infected;
		infectCount++;
		break;
	case  infected:
		direction = { this->direction.x, -this->direction.y };
		grid[position.str()] = flagged;
		break;
	case  flagged:
		direction = { -this->direction.y, -this->direction.x };
		grid[position.str()] = clean;
		break;
	}

	position.add(&direction);
}

void Day22::part1() {
	CarrierGrid grid(&fileContent);

	for (int i = 0; i < 10000; i++) {
		grid.tick();
	}

	printResult(grid.infectCount);
}

void Day22::part2() {
	CarrierGrid grid(&fileContent);

	for (int i = 0; i < 10000000; i++) {
		grid.tickMulti();
	}

	printResult(grid.infectCount);
}