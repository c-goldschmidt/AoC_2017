#pragma once

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"
#include "day8.hpp"
#include "day9.hpp"
#include "day10.hpp"
#include "day11.hpp"
#include "day12.hpp"
#include "day13.hpp"
#include "day14.hpp"
#include "day15.hpp"
#include "day16.hpp"
#include "day17.hpp"
#include "day18.hpp"
#include "day19.hpp"
#include "day20.hpp"
#include "day21.hpp"
#include "day22.hpp"
#include "day23.hpp"
#include "day24.hpp"
#include "day25.hpp"

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
