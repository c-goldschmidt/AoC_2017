#pragma once

#include "includes.h"

vector<string> split(string strIn, string rx) {
	regex rxSplit(rx);
	return { sregex_token_iterator(strIn.begin(), strIn.end(), rxSplit, -1), {} };
}

inline long long PerformanceCounter() noexcept {
    LARGE_INTEGER li;
    ::QueryPerformanceCounter(&li);
    return li.QuadPart;
}

inline long long PerformanceFrequency() noexcept {
    LARGE_INTEGER li;
    ::QueryPerformanceFrequency(&li);
    return li.QuadPart;
}

struct Point2D {
	long long y = 0;
	long long x = 0;
	void add(Point2D* other) {
		x += other->x;
		y += other->y;
	};

	string str() {
		stringstream ss;
		ss << y << "," << x;
		return ss.str();
	}

	long long centerDist() {
		return abs(x) + abs(y);
	};

	long long dist(Point2D* other) {
		return abs(other->x - x) + abs(other->y - y);
	};
};

struct Point3D {
	long long x = 0;
	long long y = 0;
	long long z = 0;
	void add(Point3D* other) {
		x += other->x;
		y += other->y;
		z += other->z;
	};

	long long centerDist() {
		return abs(x) + abs(y) + abs(z);
	};

	long long dist(Point3D* other) {
		return abs(other->x - x) + abs(other->y - y) + abs(other->z - z);
	};
};
