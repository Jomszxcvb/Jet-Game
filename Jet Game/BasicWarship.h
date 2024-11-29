#pragma once

#include <GL/glut.h>
#include <algorithm>

class BasicWarship {
public:
    BasicWarship();
    ~BasicWarship();
    float getPosX() const;
    float getPosY() const;
    float getSize() const;
    void setPosX(float x);
    void setPosY(float y);
    void render();
    void update(float speed);
    bool canFireMissile() const;
    void resetMissileTimer();

private:
    float posX, posY;
    float size;
    float attackSpeed;
    float missileTimer;
    GLfloat bodyVertices[24];
    GLfloat frontWingsVertices[18];
    GLfloat thrustersVertices[60];
};