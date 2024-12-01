#pragma once

#include <GL/glew.h>
#include <vector>

class ScoringSystem {
private:
	int totalScore;

public:
	ScoringSystem();
	~ScoringSystem();

	void updateScore(int points);
	void render(float alpha);
};