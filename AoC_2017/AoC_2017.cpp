#include <iostream>
#include <string>

#include "day_factory.hpp"
#include "days.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		runDay("1");
	} else {
		runDay(argv[1]);
	}

}
