#include "Missile.h"

void Missile::initVBO()
{
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

Missile::~Missile()
{
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

void Missile::render()
{
    glPointSize(5.0f); // Set point size for visibility
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, 0);

    // Update VBO with the current position
    float position[] = { posX, posY };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(position), position);

    glDrawArrays(GL_POINTS, 0, 1); // Render a single point
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Missile::update(float speed) {
    posX += directionX * speed;
    posY += directionY * speed;
    if (posX < -1.0f || posX > 1.0f || posY < -1.0f || posY > 1.0f) {
        outOfBound = true;
    }
}

void Missile::scale(float scaleX, float scaleY)
{
    size *= scaleX;
}

bool Missile::isOutOfBound() const
{
    return outOfBound;
}

float Missile::getMissileSpeed() const {
	return missileSpeed;
}

void Missile::setMissileSpeed(float speed) {
	missileSpeed = speed;
}
