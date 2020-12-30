#pragma once
#include "day_factory.hpp"

struct Picture {
	uint size = 0;
	vector<vector<bool>> pixels;
};

DAY(Day21)

Picture makePic(uint size) {
	vector<vector<bool>> pixels;
	for (uint i = 0; i < size; i++) {
		vector<bool> line;
		for (uint j = 0; j < size; j++) {
			line.push_back(false);
		}
		pixels.push_back(line);
	}

	return { size, pixels };
}

Picture copy(Picture* input) {
	Picture result = makePic(input->size);

	for (uint i = 0; i < input->size; i++) {
		for (uint j = 0; j < input->size; j++) {
			result.pixels[i][j] = input->pixels[i][j];
		}
	}

	return result;
}

string picToString(Picture* input) {
	stringstream ss;

	for (uint row = 0; row < input->size; row++) {
		for (auto col : input->pixels[row]) {
			ss << (col ? "#" : ".");
		}
		if (row < input->size - 1) {
			ss << "/";
		}
	}

	return ss.str();
}

Picture rotate(Picture *input, int times) {
	Picture result = copy(input);

	for (int i = 0; i < times; i++) {
		Picture subResult = makePic(result.size);

		for (uint row = 0; row < input->size; row++) {
			for (uint col = 0; col < input->size; col++) {
				uint colNew = row;
				uint rowNew = (input->size - 1) - col;
				subResult.pixels[rowNew][colNew] = result.pixels[row][col];
			}
		}
		result = subResult;
	}

	return result;
}

Picture mirrorHoriz(Picture* input) {
	Picture result = makePic(input->size);

	for (uint row = 0; row < input->size; row++) {
		for (uint col = 0; col < input->size; col++) {
			result.pixels[row][col] = input->pixels[row][input->size - 1 - col];
		}
	}

	return result;
}

Picture mirrorVert(Picture* input) {
	Picture result = makePic(input->size);

	for (uint row = 0; row < input->size; row++) {
		for (uint col = 0; col < input->size; col++) {
			result.pixels[row][col] = input->pixels[input->size - 1 - row][col];
		}
	}

	return result;
}

vector<string> permutations(Picture *input) {
	Picture horiz = mirrorHoriz(input);
	Picture vert = mirrorVert(input);
	Picture vertHoriz = mirrorVert(&horiz);

	Picture rot1 = rotate(&horiz, 1);
	Picture rot2 = rotate(&horiz, 2);
	Picture rot3 = rotate(&horiz, 3);

	vector<Picture> perms = {
		*input,
		rotate(input, 1),
		rotate(input, 2),
		rotate(input, 3),
		rotate(&horiz, 1),
		rotate(&horiz, 2),
		rotate(&horiz, 3),
		rotate(&vert, 2),
	};

	vector<string> result;
	for (auto p: perms) {
		result.push_back(picToString(&p));
	}
	
	return result;
}

void printPicture(Picture* input) {
	for (auto row: input->pixels) {
		for (auto col: row) {
			cout << (col ? "#" : ".");
		}
		cout << endl;
	}
}

Picture stringToPic(string input) {
	vector<string> lines = split(input, "/");
	uint size = lines.size();
	vector<vector<bool>> pixels;

	for (string line: lines) {
		vector<bool> lineData;
		for (char chr: line) {
			lineData.push_back(chr == '#');
		}
		pixels.push_back(lineData);
	}

	return { size, pixels };
}

vector<vector<Picture>> dividePicture(Picture *pic) {
	vector<vector<Picture>> output;

	uint mod = 0;
	if (pic->size % 2 == 0) {
		mod = 2;
	} else {
		mod = 3;
	}

	vector<Picture> picRow;
	for (uint row = 0; row < pic->size; row++) {
		if (row % mod == 0) {
			if (row > 0) {
				output.push_back(picRow);
			}
			picRow = vector<Picture>();
		}

		uint picIndex = -1;
		for (uint col = 0; col < pic->size; col++) {
			if (col % mod == 0) {
				picIndex++;
			}

			if (picIndex >= picRow.size()) {
				picRow.push_back(makePic(mod));
			}

			picRow[picIndex].pixels[row % mod][col % mod] = pic->pixels[row][col];
		}
	}
	output.push_back(picRow);
	return output;
}

Picture combinePictures(vector<vector<Picture>> *input) {
	// note: all sub-pics are of even, square size
	uint itemSize = input->at(0).at(0).size;
	Picture result = makePic(itemSize * input->size());

	for (uint row = 0; row < input->size(); row++) {
		for (uint col = 0; col < input->size(); col++) {
			Picture pic = input->at(row).at(col);
			for (uint i = 0; i < itemSize; i++) {
				for (uint j = 0; j < itemSize; j++) {
					result.pixels[row * itemSize + i][col * itemSize + j] = pic.pixels[i][j];
				}
			}
		}
	}
	return result;
}

Picture getReplacement(Picture* input, map<string, string>* replacements) {
	auto perms = permutations(input);

	for (auto perm : perms) {
		if (auto it = replacements->find(perm); it != replacements->end()) {
			return stringToPic(it->second);
		}
	}

	throw "no replacement found, missing permutations";
}

Picture expand(Picture* input, map<string, string>* replacements) {
	auto divided = dividePicture(input);
	vector<vector<Picture>> replaced;
	
	for (auto row: divided) {
		vector<Picture> newRow;
		for (auto col : row) {
			newRow.push_back(getReplacement(&col, replacements));
		}
		replaced.push_back(newRow);
	}

	return combinePictures(&replaced);
}

map<string, string> getReplacements(vector<string> *input) {
	map<string, string> result;

	for (auto it = input->begin(); it != input->end(); it++) {
		auto line = split(*it, " => ");
		result[line[0]] = line[1];
	}

	return result;
}

int countTrue(Picture *picture) {
	int count = 0;
	for (auto row: picture->pixels) {
		for (auto col : row) {
			if (col) {
				count++;
			}
		}
	}
	return count;
}

Picture iterate(vector<string> *input, int iterations) {
	auto replacements = getReplacements(input);
	Picture start = stringToPic(".#./..#/###");

	for (int i = 0; i < iterations; i++) {
		start = expand(&start, &replacements);
	}

	return start;
}

void Day21::part1() {
	auto pic = iterate(&fileContent, 5);
	printResult(countTrue(&pic));
}

void Day21::part2() {
	// meh...about 40s...
	auto pic = iterate(&fileContent, 18);
	printResult(countTrue(&pic));
}