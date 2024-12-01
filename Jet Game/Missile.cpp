#include "Missile.h"
#include <utility>

void Missile::initVBO() {
    // Define the initial position of the player (as a point)
    float position[] = { posX, posY };

    glGenBuffers(1, &vbo);              // Generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW); // Load the initial data
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Unbind the buffer
}

Missile::Missile(float x, float y, float size, float dirX, float dirY)
    : posX(x), posY(y), size(size), missileSpeed(0.01f), outOfBound(false), directionX(dirX), directionY(dirY) {
    initVBO();
}

Missile::~Missile() {
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}

float Missile::getPosX() const {
    return posX;
}

float Missile::getPosY() const {
    return posY;
}

float Missile::getSize() const {
    return size;
}

void Missile::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(size, size, 1.0f); // Scale the missile based on its size
    renderOuterBullet();
    renderMiddleBullet();
    renderInnerBullet();
    glPopMatrix();
}

void Missile::renderOuterBullet() const {
    GLfloat outerVertices[] = {
        -0.1f, 0.8f, 0.0f,
        -0.25f, 0.575f, 0.0f,
        -0.25f, 0.195f, 0.0f,
        0.0f, -0.8f, 0.0f,
        0.25f, 0.195f, 0.0f,
        0.25f, 0.575f, 0.0f,
        0.1f, 0.8f, 0.0f,
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 6 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(0, 51, 204);
    glVertexPointer(3, GL_FLOAT, 0, outerVertices);
    glDrawElements(GL_POLYGON, 7, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Missile::renderMiddleBullet() const {
    GLfloat middleVertices[] = {
        -0.075f, 0.75f, 0.0f,
        -0.2f, 0.55f, 0.0f,
        -0.2f, 0.2f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.2f, 0.2f, 0.0f,
        0.2f, 0.55f, 0.0f,
        0.075f, 0.75f, 0.0f,
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 6 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(0, 153, 255);
    glVertexPointer(3, GL_FLOAT, 0, middleVertices);
    glDrawElements(GL_POLYGON, 7, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Missile::renderInnerBullet() const {
    GLfloat innerVertices[] = {
        -0.05f, 0.675f, 0.0f,
        -0.12f, 0.525f, 0.0f,
        0.0f, -0.2f, 0.0f,
        0.12f, 0.525f, 0.0f,
        0.05f, 0.675f, 0.0f,
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(230, 230, 255);
    glVertexPointer(3, GL_FLOAT, 0, innerVertices);
    glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Missile::update(float speed) {
    posX += directionX * speed;
    posY += directionY * speed;
    if (posX < -1.0f || posX > 1.0f || posY < -1.0f || posY > 1.0f) {
        outOfBound = true;
    }
}

void Missile::scale(float scaleX, float scaleY) {
    size *= std::min(scaleX, scaleY); // Scale the size by the smaller of the two factors
}

bool Missile::isOutOfBound() const {
    return outOfBound;
}

float Missile::getMissileSpeed() const {
    return missileSpeed;
}

void Missile::setMissileSpeed(float speed) {
    missileSpeed = speed;
}
