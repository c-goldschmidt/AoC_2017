#pragma once
#include "day_factory.hpp"

DAY(Day7)

struct TreeNode {
	string name;
	int weight;
	vector<string> children;
};

string getRoot(vector<string> fileContent, map<string, TreeNode> *nodes) {
	map<string, string> parents;
	vector<string> nodeNames;
	regex rxNode("(\\w+) \\((\\d+\\))(?: -> (.+)$|$)");

	for (string node : fileContent) {
		smatch match;
		regex_match(node, match, rxNode);

		TreeNode asNode;
		asNode.name = match[1];
		asNode.weight = stoi(match[2]);

		if (match[3].length() > 0) {
			vector<string> nodeContent = split(match[3], ", ");
			asNode.children = nodeContent;

			for (string child: nodeContent) {
				parents[child] = asNode.name;
			}
		}

		nodes->insert(pair(asNode.name, asNode));
		nodeNames.push_back(asNode.name);
	}

	string root;
	for (auto nodeName: nodeNames) {
		auto parent = parents.find(nodeName);
		if (parent == parents.end()) {
			return nodeName;
		}
	}
}

int getWeight(string nodeName, map<string, TreeNode> *nodes) {
	TreeNode node = nodes->at(nodeName);
	int weight = node.weight;

	for (string child : node.children) {
		weight += getWeight(child, nodes);
	}
	return weight;
}

int findUnbalanced(string nodeName, map<string, TreeNode>* nodes) {
	TreeNode node = nodes->at(nodeName);
	for (string child: node.children) {
		int sub = findUnbalanced(child, nodes);
		if (sub > 0) {
			return sub;
		}
	}

	if (node.children.size() == 0) {
		return 0;
	}

	map<int, int> balance;
	map<int, string> balanceNodes;

	for (string child: node.children) {
		int childWeight = getWeight(child, nodes);

		if (auto it = balance.find(childWeight); it == balance.end()) {
			balance[childWeight] = 0;
		}
		balance[childWeight]++;
		balanceNodes[childWeight] = child;
	}

	if (balance.size() == 1) {
		return 0;
	}

	for (auto item: balance) {
		if (item.second == 1) {
			int targetWeight = -1;
			for (auto subItem : balance) {
				if (subItem.second > 1) {
					targetWeight = subItem.first;
					break;
				}
			}

			int diff = item.first - targetWeight;
			TreeNode targetNode = nodes->at(balanceNodes[item.first]);
			return targetNode.weight - diff;
		}
	}

	return 0;
}

void Day7::part1() {
	map<string, TreeNode> nodes;
	string root = getRoot(fileContent, &nodes);
	printResult(root);
}

void Day7::part2() {
	map<string, TreeNode> nodes;
	string root = getRoot(fileContent, &nodes);
	int rebalance = findUnbalanced(root, &nodes);
	printResult(rebalance);
}