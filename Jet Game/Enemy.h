#pragma once
#include "Jet.h"
class Enemy :
    public Jet {
private:
	float posX, posY; // Position
	float speed; // Movement speed
	int health; // Health points
	int width, height; // Size of the player sprite

public:
	void spawn();
	void move();
	void takeDamage(int damage) override;
	void draw() override;
};

