#include "PowerUp.h"
#include <GL/glut.h>

PowerUp::PowerUp(PowerUpType type, float x, float y) : type(type), posX(x), posY(y), speed(2.0f) {}

void PowerUp::update(float deltaTime, float playerX, float playerY) {
    // Move towards the player
    float directionX = playerX - posX;
    float directionY = playerY - posY;
    float length = sqrt(directionX * directionX + directionY * directionY);
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }
    posX += directionX * speed * deltaTime;
    posY += directionY * speed * deltaTime;
}

bool PowerUp::checkCollision(float playerX, float playerY, float playerSize) const {
    return (std::abs(posX - playerX) < playerSize && std::abs(posY - playerY) < playerSize);
}

PowerUpType PowerUp::getType() const {
    return type;
}

void PowerUp::getColor(float& r, float& g, float& b) const {
    switch (type) {
    case PowerUpType::HomingMissile:
        r = 1.0f; g = 0.0f; b = 0.0f; // Red color for HomingMissile
        break;
    case PowerUpType::Gigantification:
        r = 0.0f; g = 0.0f; b = 1.0f; // Blue color for Gigantification
        break;
    }
}

void PowerUp::render() const {
    float r, g, b;
    getColor(r, g, b);

    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(r, g, b); // Set color based on power-up type
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(0.05f, 0.05f);
    glVertex2f(-0.05f, 0.05f);
    glEnd();
    glPopMatrix();
}