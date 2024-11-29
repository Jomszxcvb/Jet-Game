#pragma once
#include <GL/glew.h>
#include <vector>

#include "Missile.h"

class Player
{
private:
	// Player position
	float posX, posY;
	// Size of the player sprite
	float size; 

	// Jet vertices
	GLfloat bodyVertices[36];
	GLfloat frontWingsVertices[36];
	GLfloat thrustersVertices[24];
	GLfloat finsVertices[24];
	GLfloat backWingsVertices[30];

	// Vector to store the missiles
	std::vector<Missile> missiles;
	// Speed of missile launch and movement
	float missileSpeed;

public:
	Player();
	~Player();

	void render();
	void update(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, float speed);

	void launchMissile();
	bool checkCollision(float objX, float objY, float objWidth, float objHeight) const;

	// Getters for position
	float getX() const;
	float getY() const;

	// Method to scale the player based on the window size
	void scale(float scaleX, float scaleY);
};
