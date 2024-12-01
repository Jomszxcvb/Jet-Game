#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

#include "Missile.h"

class Player {
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
    float attackSpeed;

    // Number of hearts
    int hearts;

    // Invincibility state
    bool invincible;
    float invincibleTimer;

    bool blinkState;

public:
    Player();
    ~Player();

    void render();
    void update(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, float speed, const std::vector<Missile*>& enemyMissiles);

    bool checkCollision(float objX, float objY, float objWidth, float objHeight) const;

    // Getters for position
    float getX() const;
    float getY() const;
	float getSize() const;

    float getAttackSpeed() const;

    // Method to scale the player based on the window size
    void scale(float scaleX, float scaleY);

    // Heart system methods
    int getHearts() const;
    void decreaseHeart();
    void resetHearts();

    void handleCollisionWithEnemyMissile(float missileX, float missileY, float missileSize);

    // Invincibility methods
    bool isInvincible() const;
    void setInvincible(bool state);

    // Render hearts
    void renderHearts() const;

    // Method to handle player taking damage
    void takeDamage();
};