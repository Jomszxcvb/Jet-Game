#include "Player.h"

#include <iostream>
#include <algorithm>

Player::Player() : posX(0.0f), posY(0.0f), size(0.1f), attackSpeed(0.3f), hearts(5), invincible(false), invincibleTimer(0.0f), blinkState(false) {
    // Initialize the jet body vertices
    GLfloat body[] = {
        0.0f, 0.95f, 0.0f, -0.05f, 0.825f, 0.0f, -0.07f, 0.535f, 0.0f, -0.1725f, 0.475f, 0.0f, -0.2f, 0.2f, 0.0f, -0.166f, -0.375f, 0.0f,
        0.166f, -0.375f, 0.0f, 0.2f, 0.2f, 0.0f, 0.1725f, 0.475f, 0.0f, 0.07f, 0.535f, 0.0f, 0.05f, 0.825f, 0.0f, 0.0f, 0.95f, 0.0f
    };
    std::copy(std::begin(body), std::end(body), bodyVertices);

    // Initialize the front wings vertices
    GLfloat frontWings[] = {
        -0.2f, 0.2f, 0.0f, -0.66f, -0.166f, 0.0f, -0.62f, -0.3f, 0.0f, -0.5f, -0.35f, 0.0f, -0.235f, -0.245f, 0.0f, -0.175f, -0.26f, 0.0f,
        0.175f, -0.26f, 0.0f, 0.235f, -0.245f, 0.0f, 0.5f, -0.35f, 0.0f, 0.62f, -0.3f, 0.0f, 0.66f, -0.166f, 0.0f, 0.2f, 0.2f, 0.0f
    };
    std::copy(std::begin(frontWings), std::end(frontWings), frontWingsVertices);

    // Initialize the thrusters vertices
    GLfloat thrusters[] = {
        -0.166f, -0.375f, 0.0f, -0.120f, -0.51f, 0.0f, -0.044f, -0.51f, 0.0f, 0.0f, -0.375f, 0.0f,
        0.0f, -0.375f, 0.0f, 0.044f, -0.51f, 0.0f, 0.120f, -0.51f, 0.0f, 0.166f, -0.375f, 0.0f
    };
    std::copy(std::begin(thrusters), std::end(thrusters), thrustersVertices);

    // Initialize the fins vertices
    GLfloat fins[] = {
        -0.1f, -0.185f, 0.0f, -0.25f, -0.28f, 0.0f, -0.25f, -0.45f, 0.0f, -0.1f, -0.36f, 0.0f,
        0.1f, -0.36f, 0.0f, 0.25f, -0.45f, 0.0f, 0.25f, -0.28f, 0.0f, 0.1f, -0.185f, 0.0f
    };
    std::copy(std::begin(fins), std::end(fins), finsVertices);

    // Initialize the back wings vertices
    GLfloat backWings[] = {
        -0.1f, -0.22f, 0.0f, -0.38f, -0.52f, 0.0f, -0.38f, -0.615f, 0.0f, -0.24f, -0.66f, 0.0f, -0.1f, -0.55f, 0.0f,
        0.1f, -0.22f, 0.0f, 0.38f, -0.52f, 0.0f, 0.38f, -0.615f, 0.0f, 0.24f, -0.66f, 0.0f, 0.1f, -0.55f, 0.0f
    };
    std::copy(std::begin(backWings), std::end(backWings), backWingsVertices);
}

Player::~Player() {

}

void Player::render() {
    if (invincible && blinkState) {
        return; // Skip rendering when blinkState is true
    }

    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(size, size, 1.0f);

    // Render the jet body
    GLubyte bodyIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(112, 146, 190);
    glVertexPointer(3, GL_FLOAT, 0, bodyVertices);
    glDrawElements(GL_POLYGON, 12, GL_UNSIGNED_BYTE, bodyIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the front wings
    GLubyte frontWingsIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(96, 125, 163);
    glVertexPointer(3, GL_FLOAT, 0, frontWingsVertices);
    glDrawElements(GL_POLYGON, 12, GL_UNSIGNED_BYTE, frontWingsIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the thrusters
    GLubyte thrustersIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(54, 70, 92);
    glVertexPointer(3, GL_FLOAT, 0, thrustersVertices);
    glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE, thrustersIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the fins
    GLubyte finsIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(135, 176, 230);
    glVertexPointer(3, GL_FLOAT, 0, finsVertices);
    glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE, finsIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the back wings
    GLubyte leftBackWingsIndices[] = { 0, 1, 2, 3, 4 };
    GLubyte rightBackWingsIndices[] = { 5, 6, 7, 8, 9 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(96, 125, 163);
    glVertexPointer(3, GL_FLOAT, 0, backWingsVertices);
    glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, leftBackWingsIndices);
    glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, rightBackWingsIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Player::update(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, float speed, const std::vector<Missile*>& enemyMissiles) {
    // Update player position and handle collisions
    if (!invincible) {
        for (const Missile* missile : enemyMissiles) {
            if (checkCollision(missile->getPosX(), missile->getPosY(), missile->getSize(), missile->getSize())) {
                takeDamage();
                break;
            }
        }
    }

    // Update invincibility timer
    if (invincible) {
        invincibleTimer += 0.016f; // Assuming update is called every 16ms (60 FPS)
        if (static_cast<int>(invincibleTimer * 10) % 2 == 0) {
            blinkState = !blinkState; // Toggle blink state every 100ms
        }
        if (invincibleTimer >= 2.0f) { // 2 seconds of invincibility
            invincible = false;
            invincibleTimer = 0.0f;
            blinkState = false;
        }
    }

    // Update player position based on input
    if (moveUp) posY += speed;
    if (moveDown) posY -= speed;
    if (moveLeft) posX -= speed;
    if (moveRight) posX += speed;

    // Ensure the player does not go past the screen boundaries
    float halfSize = size / 2.0f;
    if (posX - halfSize < -1.0f) posX = -1.0f + halfSize;
    if (posX + halfSize > 1.0f) posX = 1.0f - halfSize;
    if (posY - halfSize < -1.0f) posY = -1.0f + halfSize;
    if (posY + halfSize > 1.0f) posY = 1.0f - halfSize;
}

bool Player::checkCollision(float objX, float objY, float objWidth, float objHeight) const {
    // Collision detection logic
    return (posX < objX + objWidth && posX + size > objX && posY < objY + objHeight && posY + size > objY);
}


float Player::getX() const {
    return posX;
}

float Player::getY() const
{
	return posY;
}

float Player::getSize() const {
	return size;
}

float Player::getAttackSpeed() const {
	return attackSpeed;
}

// Method to scale the player based on the window size
void Player::scale(float scaleX, float scaleY) {
    posX *= scaleX;
    posY *= scaleY;
}

int Player::getHearts() const {
    return hearts;
}

void Player::decreaseHeart() {
    if (!invincible) {
        hearts--;
        invincible = true;
        invincibleTimer = 0.0f;
        std::cout << "Player hit! Hearts remaining: " << hearts << std::endl;
    }
}

void Player::resetHearts() {
    hearts = 5;
}

void Player::handleCollisionWithEnemyMissile(float missileX, float missileY, float missileSize) {
    if (checkCollision(missileX, missileY, missileSize, missileSize)) {
        takeDamage();
    }
}

bool Player::isInvincible() const {
    return invincible;
}

void Player::setInvincible(bool state) {
    invincible = state;
    if (state) {
        invincibleTimer = 0.0f;
    }
}

void Player::renderHearts() const {
    float heartSize = 0.05f;
    float startX = -0.9f; // Starting position for the hearts
    float startY = 0.9f;  // Position near the top-left corner

    for (int i = 0; i < hearts; ++i) {
        float x = startX + i * (heartSize + 0.02f); // Spacing between hearts

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); // Red color for hearts

        // Center of the heart
        glVertex2f(x, startY - heartSize / 2);

        // Top left curve
        for (int j = 0; j <= 180; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(x + heartSize * 0.5f * cos(angle) - heartSize * 0.25f, startY - heartSize * 0.5f * sin(angle));
        }

        // Top right curve
        for (int j = 180; j <= 360; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(x + heartSize * 0.5f * cos(angle) + heartSize * 0.25f, startY - heartSize * 0.5f * sin(angle));
        }

        // Bottom point
        glVertex2f(x, startY - heartSize);

        glEnd();
    }
}

void Player::takeDamage() {
    if (!invincible) {
        decreaseHeart();
        setInvincible(true);
    }
}