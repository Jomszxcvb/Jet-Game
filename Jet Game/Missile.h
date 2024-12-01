#pragma once
#include <GL/glew.h>

class Missile {
public:
    Missile(float x = 0.0f, float y = 0.0f, float size = 0.01f, float dirX = 0.0f, float dirY = 1.0f);
    ~Missile();
    float getPosX() const;
    float getPosY() const;
    float getSize() const;
    void render();
    void update(float speed);
    void scale(float scaleX, float scaleY);
    bool isOutOfBound() const;
    float getMissileSpeed() const;
    void setMissileSpeed(float speed);

private:
    void initVBO();
    void renderOuterBullet() const;
    void renderMiddleBullet() const;
    void renderInnerBullet() const;

    float posX, posY;
    float size;
    float missileSpeed;
    bool outOfBound;
    float directionX, directionY;
    GLuint vbo;
};

