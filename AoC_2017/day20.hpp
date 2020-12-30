#pragma once
#include "day_factory.hpp"

struct Particle {
	Point3D pos;
	Point3D vel;
	Point3D acc;
};

DAY(Day20)

class Particles {
public:
	Particles(vector<string> *input);
	~Particles() = default;

	uint tick(bool removeColliding = false);
	uint countParticles();
private:
	vector<Particle> particles;
	void removeCollisions();
};

Particles::Particles(vector<string> *input) {
	regex rxParticle("p=<(-?\\d+),(-?\\d+),(-?\\d+)>, v=<(-?\\d+),(-?\\d+),(-?\\d+)>, a=<(-?\\d+),(-?\\d+),(-?\\d+)>");
	for (auto it = input->begin(); it != input->end(); it++) {
		smatch match;
		regex_match(*it, match, rxParticle);

		Point3D pos = { stoll(match[1]), stoll(match[2]), stoll(match[3]) };
		Point3D vel = { stoll(match[4]), stoll(match[5]), stoll(match[6]) };
		Point3D acc = { stoll(match[7]), stoll(match[8]), stoll(match[9]) };
		Particle part = { pos, vel, acc };

		particles.push_back(part);
	}
}

uint Particles::tick(bool removeColliding) {
	for (auto it = particles.begin(); it != particles.end(); it++) {
		it->vel.add(&it->acc);
		it->pos.add(&it->vel);
	}

	if (removeColliding) {
		removeCollisions();
	}

	long long closest = LLONG_MAX;
	uint closestIndex = -1;
	for (auto it = particles.begin(); it != particles.end(); it++) {
		auto dist = it->pos.centerDist();

		if (dist < closest) {
			closest = dist;
			closestIndex = it - particles.begin();
		}
	}

	return closestIndex;
}

uint Particles::countParticles() {
	return particles.size();
}

void Particles::removeCollisions() {
	vector<uint> removeIndices;
	vector<Particle> result;
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		bool collides = false;
		for (auto it2 = particles.begin(); it2 != particles.end(); it2++) {
			if (it1 == it2) {
				continue;
			}

			if (it1->pos.dist(&it2->pos) == 0) {
				collides = true;
			}
		}
		if (!collides) {
			result.push_back(*it1);
		}
	}
	particles = result;
}

void Day20::part1() {
	Particles parts(&fileContent);

	uint idx = -1;
	for (int i = 0; i < 100; i++) {
		idx = parts.tick();
	}
	printResult(idx);
}

void Day20::part2() {
	Particles parts(&fileContent);

	uint partCount = -1;
	for (int i = 0; i < 100; i++) {
		parts.tick(true);
		partCount = parts.countParticles();
	}
	printResult(partCount);
}