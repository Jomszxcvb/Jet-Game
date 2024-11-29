#pragma once

#include <vector>
#include "Player.h"
#include "Missile.h"
#include "BasicWarship.h"
#include "ArmoredWarship.h"
#include "Controller.h"
#include "PowerUp.h"

class Game {
public:
    static Game* getInstance() {
        if (instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }

    Game();
    ~Game();

    void init(int argc, char** argv);
    void display();
    void update(int value);

private:
    static Game* instance;

    Player* player;
    std::vector<Missile*> playerMissiles;
    std::vector<Missile*> warshipMissiles;
    std::vector<Missile*> armoredWarshipMissiles;
    std::vector<BasicWarship> warships;
    std::vector<ArmoredWarship> armoredWarships;

    float missileTimer;
    float spawnTimer;
    float armoredWarshipSpawnTimer;

    std::vector<PowerUp> powerUps;
    float powerUpSpawnTimer = 0.0f;
    bool homingMissileActive = false;
    bool gigantificationActive = false;
    float powerUpEffectTimer = 0.0f;

    Controller controller;

    void spawnWarship();
    void spawnArmoredWarship();
    bool checkCollision(const Missile* missile, const BasicWarship& warship);
    bool checkCollision(const Missile* missile, const ArmoredWarship& armoredWarship);

    void spawnPowerUp(float x, float y);
    void applyPowerUp(PowerUpType type);
    void revertPowerUpEffects();

    static void displayCallback() {
        getInstance()->display();
    }

    static void updateCallback(int value) {
        getInstance()->update(value);
    }

    static void keyboardDownCallback(unsigned char key, int x, int y) {
        getInstance()->controller.keyDown(key);
    }

    static void keyboardUpCallback(unsigned char key, int x, int y) {
        getInstance()->controller.keyUp(key);
    }
};

