#pragma once
#include <GL/glut.h>

class ArmoredWarship {
public:
    ArmoredWarship();
    void render();
    void update(float deltaTime);
    bool canFireMissile() const;
    void resetMissileTimer();
    float getPosX() const;
    float getPosY() const;
    float getSize() const;
    void setPosX(float x);
    void setPosY(float y);
    void takeDamage();
    bool isDestroyed() const;

private:
    void initializeVertices();
    void renderBody();
    void renderWings();
    void renderSideThrusters();
    void renderBackThruster();
    void renderCockpit();

    float posX, posY;
    float size;
    float speed;
    float missileTimer;
    int health; // Add health attribute

    GLfloat bodyVertices[24];
    GLfloat wingsVertices[24];
    GLfloat sideThrustersVertices[120];
    GLfloat backThrusterVertices[12];
    GLfloat cockpitVertices[24];
};

