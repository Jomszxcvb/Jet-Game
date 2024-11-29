#pragma once
#include <GL/glew.h>

class Missile
{
private:
	float posX, posY; // Player position
	float size; // Size of the player sprite
	bool outOfBound; // Flag to check if the missile is out of bounds
	GLuint vbo; // Vertex buffer object for the player sprite

	// Initialize the VBO for the player sprite
	void initVBO();

public:
	Missile(float x = 0.0f, float y = 0.0f, float size = 0.01f);
	~Missile();

	void render();

	void update(float speed);

	// Method to scale the player based on the window size
	void scale(float scaleX, float scaleY);

	// Getter for outOfBound flag
	bool isOutOfBound() const;
};

