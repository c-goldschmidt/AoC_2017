#pragma once

#include "includes.h"

vector<string> split(string strIn, string rx) {
	regex rxSplit(rx);
	return { sregex_token_iterator(strIn.begin(), strIn.end(), rxSplit, -1), {} };
}
