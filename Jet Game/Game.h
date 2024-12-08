#pragma once

#include <vector>
#include "Player.h"
#include "Missile.h"
#include "BasicWarship.h"
#include "ArmoredWarship.h"
#include "Controller.h"
#include "PowerUp.h"
#include "ScoringSystem.h"

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
    void renderGameOver();
    bool isGameOver();

private:
    static Game* instance;

    Player* player;
    ScoringSystem* score;
    std::vector<Missile*> playerMissiles;
    std::vector<Missile*> warshipMissiles;
    std::vector<Missile*> armoredWarshipMissiles;
    std::vector<BasicWarship> warships;
    std::vector<ArmoredWarship> armoredWarships;
    std::vector<PowerUpType> arsenal;

    // Used for fade-in effect of Game Over
    float textAlpha;
    float textFadeSpeed;

    float missileTimer;
    float spawnTimer;
    float armoredWarshipSpawnTimer;

    std::vector<PowerUp> powerUps;
    float powerUpSpawnTimer = 0.0f;
    bool homingMissileActive = false;
    bool gigantificationActive = false;
    bool rapidFireActive = false;
    float powerUpEffectTimer = 0.0f;

    Controller controller;

    void spawnWarship();
    void spawnArmoredWarship();
    bool checkCollision(const Missile* missile, const BasicWarship& warship);
    bool checkCollision(const Missile* missile, const ArmoredWarship& armoredWarship);

    void spawnPowerUp(float x, float y);
    void applyPowerUp(PowerUpType type);
    void revertPowerUpEffects();
    void usePowerUp(PowerUpType type);
    void addToArsenal(PowerUpType type);

    const std::vector<PowerUpType>& getArsenal() const;

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

