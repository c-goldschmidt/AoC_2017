#pragma once

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"

void runDay(string dayNum) {
	unique_ptr<Day> day = DayFactory::Create("Day" + dayNum);

	if (day == nullptr) {
		cout << "could not find class for Day" << dayNum << endl;
		return;
	}

	if (!day->readFile("inputs/day" + dayNum + ".txt")) {
		cout << "could not find input file for Day" << dayNum << endl;
		return;
	}

	cout << "======= Day " << dayNum <<  " - part 1 ======" << endl;
	day->part1();

	cout << "======= Day " << dayNum << " - part 2 ======" << endl;
	day->part2();
}
