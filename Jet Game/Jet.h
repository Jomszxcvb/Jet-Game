#pragma once

#include <GL/glew.h> // <----- additional header files
#include <GL/glut.h>

#include "Missile.h"

class Jet {
private:
	float posX, posY; // Position
	float speed; // Movement speed
	int health; // Health points
	bool isAlive; // Status
	float size; // Size of the jet

public:
	virtual void move(float dx, float dy);
	virtual void shoot();
	virtual void takeDamage(int damage);

	virtual void draw();

	float getPosX() const;
	float getPosY() const;

	void setPosX(float posX);
	void setPosY(float posY);

	float getSize() const;

	void setSize(float size);
};

