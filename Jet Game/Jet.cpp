#include "Jet.h"

void Jet::move(float dx, float dy) {
	this->posX += dx;
	this->posY += dy;
}

void Jet::shoot() {
	// Missile* missile = new Missile();
}

void Jet::takeDamage(int damage) {
	this->health -= damage;
}

void Jet::draw() {
}

float Jet::getPosX() const {
	return this->posX;
}

float Jet::getPosY() const {
	return this->posY;
}

void Jet::setPosX(float posX) {
	this->posX = posX;
}

void Jet::setPosY(float posY) {
	this->posY = posY;
}
