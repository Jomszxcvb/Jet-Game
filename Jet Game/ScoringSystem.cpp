#include "ScoringSystem.h"

#include <iostream>
#include <string>
#include <sstream>
#include <GL/glut.h>

ScoringSystem::ScoringSystem() : totalScore(0) {}
ScoringSystem::~ScoringSystem() {}

void ScoringSystem::updateScore(int points) {
    totalScore += points;
}

void ScoringSystem::render() {
    glColor3f(1.0f, 1.0f, 1.0f);

    std::stringstream scoreStream;
    scoreStream << "Score: " << totalScore;
    std::string scoreText = scoreStream.str();

    const char* text = scoreText.c_str();
    void* font = GLUT_BITMAP_HELVETICA_18;

    glRasterPos2f(0.6f, 0.9f);

    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }

    glutSwapBuffers();
}