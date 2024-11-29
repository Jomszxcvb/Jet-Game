#include "BasicWarship.h"

#include <algorithm>

BasicWarship::BasicWarship() : posX(0.0f), posY(0.0f), size(0.1f), attackSpeed(1.0f), missileTimer(0.0f) {
    // Initialize the body vertices (flipped vertically)
    GLfloat body[] = {
        -0.035f, -0.7f, 0.0f,
        -0.085f, -0.65f, 0.0f,
        -0.19f, -0.295f, 0.0f,
        -0.19f, 0.495f, 0.0f,
        0.19f, 0.495f, 0.0f,
        0.19f, -0.295f, 0.0f,
        0.085f, -0.65f, 0.0f,
        0.035f, -0.7f, 0.0f
    };
    std::copy(std::begin(body), std::end(body), bodyVertices);

    // Initialize the front wings vertices (flipped vertically)
    GLfloat frontWings[] = {
        -0.26f, -0.2f, 0.0f,
        -0.7f, 0.16f, 0.0f,
        -0.7f, 0.5f, 0.0f,
        0.7f, 0.5f, 0.0f,
        0.7f, 0.16f, 0.0f,
        0.26f, -0.2f, 0.0f
    };
    std::copy(std::begin(frontWings), std::end(frontWings), frontWingsVertices);

    // Initialize the thrusters vertices (flipped vertically)
    GLfloat thrusters[] = {
        -0.23f, -0.28f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.25f, 0.6f, 0.0f,
        -0.15f, 0.6f, 0.0f,
        -0.15f, -0.25f, 0.0f,
        -0.17f, -0.28f, 0.0f,
        -0.24f, 0.6f, 0.0f,
        -0.23f, 0.63f, 0.0f,
        -0.17f, 0.63f, 0.0f,
        -0.16f, 0.6f, 0.0f,
        0.23f, -0.28f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.25f, 0.6f, 0.0f,
        0.15f, 0.6f, 0.0f,
        0.15f, -0.25f, 0.0f,
        0.17f, -0.28f, 0.0f,
        0.24f, 0.6f, 0.0f,
        0.23f, 0.63f, 0.0f,
        0.17f, 0.63f, 0.0f,
        0.16f, 0.6f, 0.0f
    };
    std::copy(std::begin(thrusters), std::end(thrusters), thrustersVertices);
}

BasicWarship::~BasicWarship() {
    // Destructor logic if needed
}

float BasicWarship::getPosX() const {
    return posX;
}

float BasicWarship::getPosY() const {
    return posY;
}

float BasicWarship::getSize() const {
    return size;
}

void BasicWarship::setPosX(float x) {
    posX = x;
}

void BasicWarship::setPosY(float y) {
    posY = y;
}

void BasicWarship::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(size, size, 1.0f);

    // Render the body
    GLubyte bodyIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(196, 133, 83);
    glVertexPointer(3, GL_FLOAT, 0, bodyVertices);
    glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_BYTE, bodyIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the front wings
    GLubyte frontWingsIndices[] = { 0, 1, 2, 3, 4, 5 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(150, 102, 64);
    glVertexPointer(3, GL_FLOAT, 0, frontWingsVertices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, frontWingsIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Render the thrusters
    GLubyte thrustersIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(230, 156, 97);
    glVertexPointer(3, GL_FLOAT, 0, thrustersVertices);
    glDrawElements(GL_POLYGON, 20, GL_UNSIGNED_BYTE, thrustersIndices);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void BasicWarship::update(float speed) {
    posY -= speed;
    missileTimer += 0.016f; // Assuming update is called every 16ms 
}

bool BasicWarship::canFireMissile() const {
    return missileTimer >= attackSpeed;
}

void BasicWarship::resetMissileTimer() {
    missileTimer = 0.0f;
}
