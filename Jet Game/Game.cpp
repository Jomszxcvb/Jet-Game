#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

Game* Game::instance = nullptr;

Game::Game() : player(nullptr), missileTimer(0.0f), spawnTimer(0.0f) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed
    instance = this;
}

Game::~Game() {
    delete player;
    for (Missile* missile : playerMissiles) {
        delete missile;
    }
    for (Missile* missile : warshipMissiles) {
        delete missile;
    }
}

void Game::init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Jet Game");

    glewInit(); // Initialize GLEW

    player = new Player();

    glutDisplayFunc(Game::displayCallback);
    glutTimerFunc(1000 / 60, Game::updateCallback, 0);
    glutKeyboardFunc(Game::keyboardDownCallback);
    glutKeyboardUpFunc(Game::keyboardUpCallback);

    glutMainLoop();
}

void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    player->renderHearts(); // Render hearts
    player->render();

    for (Missile* missile : playerMissiles) {
        missile->render();
    }

    for (Missile* missile : warshipMissiles) {
        missile->render();
    }

    for (BasicWarship& warship : warships) {
        warship.render();
    }


    glFlush();
}

void Game::update(int value) {
    if (controller.isKeyPressed(MovementKey::W)) {
        player->update(true, false, false, false, 0.01f, warshipMissiles);
    }
    if (controller.isKeyPressed(MovementKey::S)) {
        player->update(false, true, false, false, 0.01f, warshipMissiles);
    }
    if (controller.isKeyPressed(MovementKey::A)) {
        player->update(false, false, true, false, 0.01f, warshipMissiles);
    }
    if (controller.isKeyPressed(MovementKey::D)) {
        player->update(false, false, false, true, 0.01f, warshipMissiles);
    }

    // Update missile timer
    missileTimer += 0.016f; // Assuming update is called every 16ms (60 FPS)

    // Create a new missile at the player's position every 0.3 seconds
    if (missileTimer >= player->getAttackSpeed()) {
        playerMissiles.push_back(new Missile(player->getX(), player->getY(), 0.01f));
        missileTimer = 0.0f; // Reset timer
    }

    for (Missile*& missile : playerMissiles) {
        missile->update(missile->getMissileSpeed());
        if (missile->isOutOfBound()) {
            delete missile;
            missile = nullptr;
        }
    }

    // Remove nullptr entries from the playerMissiles vector
    playerMissiles.erase(std::remove_if(playerMissiles.begin(), playerMissiles.end(), [](Missile* missile) { return missile == nullptr; }), playerMissiles.end());

    // Update spawn timer
    spawnTimer += 0.016f; // Assuming update is called every 16ms (60 FPS)

    // Spawn a new warship every 2 seconds
    if (spawnTimer >= 2.0f) {
        spawnWarship();
        spawnTimer = 0.0f; // Reset timer
    }

    // Update warships and their missiles
    for (BasicWarship& warship : warships) {
        warship.update(0.001f); // Update warship with a speed value

        // Warship fires a missile towards the player
        if (warship.canFireMissile()) {
            float directionX = player->getX() - warship.getPosX();
            float directionY = player->getY() - warship.getPosY();
            float length = sqrt(directionX * directionX + directionY * directionY);
            if (length != 0) { // Avoid division by zero
                directionX /= length;
                directionY /= length;
            }
            warshipMissiles.push_back(new Missile(warship.getPosX(), warship.getPosY(), 0.01f, directionX, directionY));
            warship.resetMissileTimer();
        }
    }

    for (Missile*& missile : warshipMissiles) {
        missile->update(missile->getMissileSpeed());
        if (missile->isOutOfBound()) {
            delete missile;
            missile = nullptr;
        }
    }

    // Remove nullptr entries from the warshipMissiles vector
    warshipMissiles.erase(std::remove_if(warshipMissiles.begin(), warshipMissiles.end(), [](Missile* missile) { return missile == nullptr; }), warshipMissiles.end());

    // Check for collisions between player missiles and warships
    for (auto warshipIt = warships.begin(); warshipIt != warships.end();) {
        bool warshipDestroyed = false;
        for (auto missileIt = playerMissiles.begin(); missileIt != playerMissiles.end();) {
            if (checkCollision(*missileIt, *warshipIt)) {
                delete* missileIt;
                missileIt = playerMissiles.erase(missileIt);
                warshipIt = warships.erase(warshipIt);
                warshipDestroyed = true;
                break;
            }
            else {
                ++missileIt;
            }
        }
        if (!warshipDestroyed) {
            ++warshipIt;
        }
    }

    // Check for collisions between enemy missiles and player
    for (auto missileIt = warshipMissiles.begin(); missileIt != warshipMissiles.end();) {
        if (player->checkCollision((*missileIt)->getPosX(), (*missileIt)->getPosY(), (*missileIt)->getSize(), (*missileIt)->getSize())) {
            delete* missileIt;
            missileIt = warshipMissiles.erase(missileIt);
        }
        else {
            ++missileIt;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, Game::updateCallback, 0);
}

void Game::spawnWarship() {
    float randomX = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f; // Random x between -1 and 1
    BasicWarship basicWarship;
    basicWarship.setPosX(randomX);
    basicWarship.setPosY(1.0f);
    warships.push_back(basicWarship);
}

bool Game::checkCollision(const Missile* missile, const BasicWarship& basicWarship) {
    // Simple collision detection based on positions and sizes
    float missileX = missile->getPosX();
    float missileY = missile->getPosY();
    float warshipX = basicWarship.getPosX();
    float warshipY = basicWarship.getPosY();

    float distance = sqrt((missileX - warshipX) * (missileX - warshipX) + (missileY - warshipY) * (missileY - warshipY));
    return distance < (missile->getSize() + basicWarship.getSize());
}

void Game::displayCallback() {
    instance->display();
}

void Game::updateCallback(int value) {
    instance->update(value);
}

void Game::keyboardDownCallback(unsigned char key, int x, int y) {
    instance->controller.keyDown(key);
}

void Game::keyboardUpCallback(unsigned char key, int x, int y) {
    instance->controller.keyUp(key);
}
