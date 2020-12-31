#pragma once
#include "day_factory.hpp"

struct BridgePart {
	int portA;
	int portB;
	int id;
};

struct Bridge {
	vector<BridgePart *> parts;
	std::set<int> usedIds;

	void add(BridgePart *part) {
		parts.push_back(part);
		usedIds.insert(part->id);
	}

	bool has(BridgePart* part) {
		auto it = usedIds.find(part->id);
		return it != usedIds.end();
	}

	int value() {
		int result = 0;
		for (auto part: parts) {
			result += part->portA;
			result += part->portB;
		}
		return result;
	}
};

DAY(Day24)

class BridgeBuilder {
public:
	BridgeBuilder(vector<string> *input);
	~BridgeBuilder() = default;

	pair<int, int> findBestBridge(bool longest = false, Bridge prev = {}, int nextPort = 0, int depth = 0);

private:
	vector<BridgePart> parts;
};

BridgeBuilder::BridgeBuilder(vector<string>* input) {
	for (auto it = input->begin(); it != input->end(); it++) {
		auto parts = split(*it, "/");

		BridgePart part = {
			stoi(parts[0]),
			stoi(parts[1]),
			(it - input->begin()),
		};
		this->parts.push_back(part);
	}
}

pair<int, int> BridgeBuilder::findBestBridge(bool longest, Bridge prev, int nextPort, int depth) {
	vector<pair<BridgePart, int>> candidates;

	for (auto part : parts) {
		if (prev.has(&part)) {
			continue;
		}

		if (part.portA == nextPort) {
			// next = b
			candidates.push_back(pair(part, part.portB));

		} else if (part.portB == nextPort) {
			// next = a
			candidates.push_back(pair(part, part.portA));
		}
	}

	if (candidates.size() == 0) {
		return pair(prev.value(), depth);
	}

	pair<int, int> best(0, 0);
	for (auto candidate: candidates) {
		Bridge clone = { prev.parts, prev.usedIds };
		clone.add(&candidate.first);
		auto subBridge = findBestBridge(longest, clone, candidate.second, depth + 1);
		if (!longest && subBridge.first > best.first) {
			best = subBridge;
		}
		else if (longest && (subBridge.second > best.second || (subBridge.second == best.second && subBridge.first > best.first))) {
			best = subBridge;
		}
	}
	return best;
}

void Day24::part1() {
	BridgeBuilder bb(&fileContent);
	auto best = bb.findBestBridge();
	printResult(best.first);
}

void Day24::part2() {
	BridgeBuilder bb(&fileContent);
	auto best = bb.findBestBridge(true);
	printResult(best.first);
}