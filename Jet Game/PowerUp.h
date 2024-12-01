#pragma once

#include <GL/glew.h>
#include <cmath>

enum class PowerUpType {
    HomingMissile,
    Gigantification,
    RapidFire
};

class PowerUp {
public:
    PowerUp(PowerUpType type, float x, float y);

    void update(float deltaTime, float playerX, float playerY);
    bool checkCollision(float playerX, float playerY, float playerSize) const;
    PowerUpType getType() const;
    void HomingMissileSprite() const;
    void GigantificationSprite() const;
    void render() const;

private:
    PowerUpType type;
    float posX, posY;
    float speed;

    void getColor(float& r, float& g, float& b) const;
};
