#pragma once

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"

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

	print("======= Day " << dayNum <<  " - part 1 ======");
	measure(day->part1());

	print("======= Day " << dayNum << " - part 2 ======");
	measure(day->part2());
}
