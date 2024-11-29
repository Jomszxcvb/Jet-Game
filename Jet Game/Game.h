#ifndef GAME_H
#define GAME_H

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Controller.h"
#include "Player.h"
#include "Missile.h"
#include "BasicWarship.h"

class Game {
public:
    Game();
    ~Game();
    void init(int argc, char** argv);
    void display();
    void update(int value);
    void spawnWarship();
    bool checkCollision(const Missile* missile, const BasicWarship& warship);

private:
    Player* player;
    Controller controller;
    std::vector<Missile*> playerMissiles;
    std::vector<Missile*> warshipMissiles;
    std::vector<BasicWarship> warships;
    float missileTimer;
    float spawnTimer;

    static Game* instance;
    static void displayCallback();
    static void updateCallback(int value);
    static void keyboardDownCallback(unsigned char key, int x, int y);
    static void keyboardUpCallback(unsigned char key, int x, int y);
};

#endif // GAME_H
