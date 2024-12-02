#include "ArmoredWarship.h"
#include <algorithm>
#include <iostream>

ArmoredWarship::ArmoredWarship() : posX(0.0f), posY(0.0f), size(0.1f), speed(0.01f), missileTimer(0.0f), health(5) {
    initializeVertices();
}

void ArmoredWarship::takeDamage() {
    if (health > 0) {
        health--;
    }
}

bool ArmoredWarship::isDestroyed() const {
    return health <= 0;
}

void ArmoredWarship::initializeVertices() {
    // Initialize the body vertices
    GLfloat body[] = {
        -0.035f, -0.7f, 0.0f,
        -0.085f, -0.65f, 0.0f,
        -0.12f, -0.495f, 0.0f,
        -0.12f, 0.495f, 0.0f,
        0.12f, 0.495f, 0.0f,
        0.12f, -0.495f, 0.0f,
        0.085f, -0.65f, 0.0f,
        0.035f, -0.7f, 0.0f
    };
    std::copy(std::begin(body), std::end(body), bodyVertices);

    // Initialize the wings vertices
    GLfloat wings[] = {
        -0.265f, -0.22f, 0.0f,
        -0.42f, -0.22f, 0.0f,
        -0.42f, 0.42f, 0.0f,
        -0.265f, 0.42f, 0.0f,
        0.265f, 0.42f, 0.0f,
        0.42f, 0.42f, 0.0f,
        0.42f, -0.22f, 0.0f,
        0.265f, -0.22f, 0.0f
    };
    std::copy(std::begin(wings), std::end(wings), wingsVertices);

    // Initialize the side thrusters vertices
    GLfloat sideThrusters[] = {
        // left side
        -0.14f, -0.5f, 0.0f,
        -0.24f, -0.5f, 0.0f,
        -0.26f, -0.45f, 0.0f,
        -0.26f, 0.525f, 0.0f,
        -0.12f, 0.525f, 0.0f,
        -0.12f, -0.45f, 0.0f,
        // left side exhaust
        -0.255f, 0.525f, 0.0f,
        -0.235f, 0.6f, 0.0f,
        -0.145f, 0.6f, 0.0f,
        -0.125f, 0.525f, 0.0f,
        // far left side
        -0.46f, -0.69f, 0.0f,
        -0.6f, -0.69f, 0.0f,
        -0.64f, -0.65f, 0.0f,
        -0.64f, 0.54f, 0.0f,
        -0.42f, 0.54f, 0.0f,
        -0.42f, -0.65f, 0.0f,
        // far left side exhaust
        -0.635f, 0.54f, 0.0f,
        -0.615f, 0.6f, 0.0f,
        -0.445f, 0.6f, 0.0f,
        -0.425f, 0.54f, 0.0f,
        // right side
        0.14f, -0.5f, 0.0f,
        0.24f, -0.5f, 0.0f,
        0.26f, -0.45f, 0.0f,
        0.26f, 0.525f, 0.0f,
        0.12f, 0.525f, 0.0f,
        0.12f, -0.45f, 0.0f,
        // right side exhaust
        0.255f, 0.525f, 0.0f,
        0.235f, 0.6f, 0.0f,
        0.145f, 0.6f, 0.0f,
        0.125f, 0.525f, 0.0f,
        // far right side
        0.42f, -0.65f, 0.0f,
        0.46f, -0.69f, 0.0f,
        0.6f, -0.69f, 0.0f,
        0.64f, -0.65f, 0.0f,
        0.64f, 0.54f, 0.0f,
        0.42f, 0.54f, 0.0f,
        // far right side exhaust
        0.635f, 0.54f, 0.0f,
        0.615f, 0.6f, 0.0f,
        0.445f, 0.6f, 0.0f,
        0.425f, 0.54f, 0.0f
    };
    std::copy(std::begin(sideThrusters), std::end(sideThrusters), sideThrustersVertices);

    // Initialize the back thruster vertices
    GLfloat backThruster[] = {
        -0.105f, 0.495f, 0.0f,
        -0.075f, 0.59f, 0.0f,
        0.075f, 0.59f, 0.0f,
        0.105f, 0.495f, 0.0f
    };
    std::copy(std::begin(backThruster), std::end(backThruster), backThrusterVertices);

    // Initialize the cockpit vertices
    GLfloat cockpit[] = {
        -0.04f, -0.4f, 0.0f,
        -0.07f, -0.34f, 0.0f,
        -0.07f, -0.19f, 0.0f,
        -0.04f, -0.13f, 0.0f,
        0.04f, -0.13f, 0.0f,
        0.07f, -0.19f, 0.0f,
        0.07f, -0.34f, 0.0f,
        0.04f, -0.4f, 0.0f
    };
    std::copy(std::begin(cockpit), std::end(cockpit), cockpitVertices);
}

void ArmoredWarship::render() {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glScalef(size, size, 1.0f);

    renderBackThruster();
    renderWings();
    renderBody();
    renderSideThrusters();
    renderCockpit();

    glPopMatrix();

    // Check for OpenGL errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

void ArmoredWarship::update(float deltaTime) {
    posY -= speed * deltaTime;
    missileTimer += deltaTime;
}

bool ArmoredWarship::canFireMissile() const {
    return missileTimer >= 1.0f; // Fires a missile every second
}

void ArmoredWarship::resetMissileTimer() {
    missileTimer = 0.0f;
}

float ArmoredWarship::getPosX() const {
    return posX;
}

float ArmoredWarship::getPosY() const {
    return posY;
}

float ArmoredWarship::getSize() const {
    return size;
}

void ArmoredWarship::setPosX(float x) {
    posX = x;
}

void ArmoredWarship::setPosY(float y) {
    posY = y;
}

void ArmoredWarship::renderBody() {
    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(38, 66, 44);
    glVertexPointer(3, GL_FLOAT, 0, bodyVertices);
    glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ArmoredWarship::renderWings() {
    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(23, 41, 27);
    glVertexPointer(3, GL_FLOAT, 0, wingsVertices);
    glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ArmoredWarship::renderSideThrusters() {
    GLubyte leftIndices[] = { 0, 1, 2, 3, 4, 5 };
    GLubyte leftExhaustIndices[] = { 6, 7, 8, 9 };

    GLubyte farLeftIndices[] = { 10, 11, 12, 13, 14, 15 };
    GLubyte farLeftExhaustIndices[] = { 16, 17, 18, 19 };

    GLubyte rightIndices[] = { 20, 21, 22, 23, 24, 25 };
    GLubyte rightExhaustIndices[] = { 26, 27, 28, 29 };

    GLubyte farRightIndices[] = { 30, 31, 32, 33, 34, 35 };
    GLubyte farRightExhaustIndices[] = { 36, 37, 38, 39 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, sideThrustersVertices);

    // Draw side thrusters
    glColor3ub(51, 89, 59);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, leftIndices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, rightIndices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, farLeftIndices);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, farRightIndices);

    // Draw exhausts
    glColor3ub(17, 31, 20);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, leftExhaustIndices);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, rightExhaustIndices);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, farLeftExhaustIndices);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, farRightExhaustIndices);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void ArmoredWarship::renderBackThruster() {
    GLubyte indices[] = { 0, 1, 2, 3 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(17, 31, 20);
    glVertexPointer(3, GL_FLOAT, 0, backThrusterVertices);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ArmoredWarship::renderCockpit() {
    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3ub(153, 209, 255);
    glVertexPointer(3, GL_FLOAT, 0, cockpitVertices);
    glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}