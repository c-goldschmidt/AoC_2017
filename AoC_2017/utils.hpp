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