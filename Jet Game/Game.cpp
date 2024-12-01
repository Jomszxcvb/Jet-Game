#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>

Game* Game::instance = nullptr;

Game::Game() : player(nullptr), missileTimer(0.0f), spawnTimer(0.0f), armoredWarshipSpawnTimer(0.0f), textAlpha(0.0f), textFadeSpeed(0.0002f) {
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
    for (Missile* missile : armoredWarshipMissiles) {
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
    score = new ScoringSystem();

    glutDisplayFunc(Game::displayCallback);
    glutTimerFunc(1000 / 60, Game::updateCallback, 0);
    glutKeyboardFunc(Game::keyboardDownCallback);
    glutKeyboardUpFunc(Game::keyboardUpCallback);

    //Apply fade-in while rendering Game Over
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();
}

void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (!isGameOver()) { // If the player has hearts left, then render the objects
        player->renderHearts(); 
        player->render();

        score->render(1.0f); //Set the alpha of score to 1.0f
        glutSwapBuffers();

        for (Missile* missile : playerMissiles) {
            missile->render();
        }

        for (Missile* missile : warshipMissiles) {
            missile->render();
        }

        for (Missile* missile : armoredWarshipMissiles) {
            missile->render();
        }

        for (BasicWarship& warship : warships) {
            warship.render();
        }

        for (ArmoredWarship& armoredWarship : armoredWarships) {
            armoredWarship.render();
        }

        for (const PowerUp& powerUp : powerUps) {
            powerUp.render();
        }
    }
    else { // Else render Game Over message
        renderGameOver();
        score->render(textAlpha); // Used textAlpha for fade-in effect along with Game Over text

        glutSwapBuffers();
    }

    glFlush();
}

void Game::update(int value) {

    if (!isGameOver()) { // Continue updating as long as the player has hearts left
        bool moveUp = controller.isKeyPressed(InputKey::W);
        bool moveDown = controller.isKeyPressed(InputKey::S);
        bool moveLeft = controller.isKeyPressed(InputKey::A);
        bool moveRight = controller.isKeyPressed(InputKey::D);

        // Update player position continuously
        player->update(moveUp, moveDown, moveLeft, moveRight, 0.01f, warshipMissiles);

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

        // Update armored warship spawn timer
        armoredWarshipSpawnTimer += 0.016f; // Assuming update is called every 16ms (60 FPS)

        // Spawn a new armored warship every 5 seconds
        if (armoredWarshipSpawnTimer >= 5.0f) {
            spawnArmoredWarship();
            armoredWarshipSpawnTimer = 0.0f; // Reset timer
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

        // Update armored warships and their missiles
        for (ArmoredWarship& armoredWarship : armoredWarships) {
            armoredWarship.update(0.01f); // Update armored warship with a speed value

            // Armored warship fires a missile towards the player every second
            if (armoredWarship.canFireMissile()) {
                float directionX = player->getX() - armoredWarship.getPosX();
                float directionY = player->getY() - armoredWarship.getPosY();
                float length = sqrt(directionX * directionX + directionY * directionY);
                if (length != 0) { // Avoid division by zero
                    directionX /= length;
                    directionY /= length;
                }
                armoredWarshipMissiles.push_back(new Missile(armoredWarship.getPosX(), armoredWarship.getPosY(), 0.01f, directionX, directionY));
                armoredWarship.resetMissileTimer();
            }
        }

        for (Missile*& missile : warshipMissiles) {
            missile->update(missile->getMissileSpeed());
            if (missile->isOutOfBound()) {
                delete missile;
                missile = nullptr;
            }
        }

        for (Missile*& missile : armoredWarshipMissiles) {
            missile->update(missile->getMissileSpeed());
            if (missile->isOutOfBound()) {
                delete missile;
                missile = nullptr;
            }
        }

        // Remove nullptr entries from the warshipMissiles vector
        warshipMissiles.erase(std::remove_if(warshipMissiles.begin(), warshipMissiles.end(), [](Missile* missile) { return missile == nullptr; }), warshipMissiles.end());

        // Remove nullptr entries from the armoredWarshipMissiles vector
        armoredWarshipMissiles.erase(std::remove_if(armoredWarshipMissiles.begin(), armoredWarshipMissiles.end(), [](Missile* missile) { return missile == nullptr; }), armoredWarshipMissiles.end());

        // Check for collisions between player missiles and warships
        for (auto warshipIt = warships.begin(); warshipIt != warships.end();) {
            bool warshipDestroyed = false;
            for (auto missileIt = playerMissiles.begin(); missileIt != playerMissiles.end();) {
                if (checkCollision(*missileIt, *warshipIt)) {
                    float warshipX = warshipIt->getPosX();
                    float warshipY = warshipIt->getPosY();
                    delete* missileIt;
                    missileIt = playerMissiles.erase(missileIt);
                    warshipIt = warships.erase(warshipIt);
                    warshipDestroyed = true;

                    // 1/10 chance to drop a power-up at the warship's location
                    if (rand() % 10 == 0) {
                        spawnPowerUp(warshipX, warshipY);
                    }

                    break;
                }
                else {
                    ++missileIt;
                }
            }
            if (!warshipDestroyed) {
                ++warshipIt;
            }
            else {
                score->updateScore(100);
            }
        }

        // Check for collisions between player missiles and armored warships
        for (auto armoredWarshipIt = armoredWarships.begin(); armoredWarshipIt != armoredWarships.end();) {
            bool armoredWarshipDestroyed = false;
            for (auto missileIt = playerMissiles.begin(); missileIt != playerMissiles.end();) {
                if (checkCollision(*missileIt, *armoredWarshipIt)) {
                    float armoredWarshipX = armoredWarshipIt->getPosX();
                    float armoredWarshipY = armoredWarshipIt->getPosY();
                    delete* missileIt;
                    missileIt = playerMissiles.erase(missileIt);
                    armoredWarshipIt->takeDamage(); // Reduce health
                    if (armoredWarshipIt->isDestroyed()) {
                        armoredWarshipIt = armoredWarships.erase(armoredWarshipIt);
                        armoredWarshipDestroyed = true;

                        // 1/10 chance to drop a power-up at the armored warship's location
                        if (rand() % 10 == 0) {
                            spawnPowerUp(armoredWarshipX, armoredWarshipY);
                        }

                        break;
                    }
                }
                else {
                    ++missileIt;
                }
            }
            if (!armoredWarshipDestroyed) {
                ++armoredWarshipIt;
            }
            else {
                score->updateScore(300);
            }
        }

        // Check for collisions between enemy missiles and player
        for (auto missileIt = warshipMissiles.begin(); missileIt != warshipMissiles.end();) {
            if (player->checkCollision((*missileIt)->getPosX(), (*missileIt)->getPosY(), (*missileIt)->getSize(), (*missileIt)->getSize())) {
                player->takeDamage(); // Ensure player takes damage
                delete* missileIt;
                missileIt = warshipMissiles.erase(missileIt);
            }
            else {
                ++missileIt;
            }
        }

        for (auto missileIt = armoredWarshipMissiles.begin(); missileIt != armoredWarshipMissiles.end();) {
            if (player->checkCollision((*missileIt)->getPosX(), (*missileIt)->getPosY(), (*missileIt)->getSize(), (*missileIt)->getSize())) {
                player->takeDamage(); // Ensure player takes damage
                delete* missileIt;
                missileIt = armoredWarshipMissiles.erase(missileIt);
            }
            else {
                ++missileIt;
            }
        }

        // Update power-ups
        for (auto powerUpIt = powerUps.begin(); powerUpIt != powerUps.end();) {
            powerUpIt->update(0.016f, player->getX(), player->getY());
            if (powerUpIt->checkCollision(player->getX(), player->getY(), player->getSize())) {
                Game::addToArsenal(powerUpIt->getType());
                powerUpIt = powerUps.erase(powerUpIt);
            }
            else {
                ++powerUpIt;
            }
        }

        // Update power-up effects
        if (homingMissileActive || gigantificationActive || rapidFireActive) {
            powerUpEffectTimer += 0.016f;
            if (powerUpEffectTimer >= 10.0f) {
                revertPowerUpEffects();
                powerUpEffectTimer = 0.0f;
            }
        }

        // Handle power-up activation via number keys
        if (controller.isKeyPressed(InputKey::_1)) {
            Game::usePowerUp(PowerUpType::RapidFire);

        }
        if (controller.isKeyPressed(InputKey::_2)) {
            Game::usePowerUp(PowerUpType::Gigantification);
        }

        glutPostRedisplay();
        glutTimerFunc(1000 / 60, Game::updateCallback, 0);
    }
}

void Game::spawnWarship() {

    float randomX;
    bool positionValid;

    do {
        randomX = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f; // Random x between -1 and 1
        positionValid = true;

        for (const BasicWarship& warship : warships) {
            if (std::abs(randomX - warship.getPosX()) < warship.getSize()) {
                positionValid = false;
                break;
            }
        }

        for (const ArmoredWarship& armoredWarship : armoredWarships) {
            if (std::abs(randomX - armoredWarship.getPosX()) < armoredWarship.getSize()) {
                positionValid = false;
                break;
            }
        }
    } while (!positionValid);

    BasicWarship basicWarship;
    basicWarship.setPosX(randomX);
    basicWarship.setPosY(1.0f);
    warships.push_back(basicWarship);
}

void Game::spawnArmoredWarship() {
    float randomX;
    bool positionValid;

    do {
        randomX = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f; // Random x between -1 and 1
        positionValid = true;

        for (const BasicWarship& warship : warships) {
            if (std::abs(randomX - warship.getPosX()) < warship.getSize()) {
                positionValid = false;
                break;
            }
        }

        for (const ArmoredWarship& armoredWarship : armoredWarships) {
            if (std::abs(randomX - armoredWarship.getPosX()) < armoredWarship.getSize()) {
                positionValid = false;
                break;
            }
        }
    } while (!positionValid);

    ArmoredWarship armoredWarship;
    armoredWarship.setPosX(randomX);
    armoredWarship.setPosY(1.0f);
    armoredWarships.push_back(armoredWarship);
}

bool Game::checkCollision(const Missile* missile, const BasicWarship& warship) {
    // Implement collision detection logic for BasicWarship
    // Example logic:
    float missileX = missile->getPosX();
    float missileY = missile->getPosY();
    float warshipX = warship.getPosX();
    float warshipY = warship.getPosY();
    float warshipSize = warship.getSize();

    return (std::abs(missileX - warshipX) < warshipSize && std::abs(missileY - warshipY) < warshipSize);
}

bool Game::checkCollision(const Missile* missile, const ArmoredWarship& warship) {
    // Implement collision detection logic for ArmoredWarship
    // Example logic:
    float missileX = missile->getPosX();
    float missileY = missile->getPosY();
    float warshipX = warship.getPosX();
    float warshipY = warship.getPosY();
    float warshipSize = warship.getSize();

    return (std::abs(missileX - warshipX) < warshipSize && std::abs(missileY - warshipY) < warshipSize);
}

void Game::spawnPowerUp(float x, float y) {
    PowerUpType type = static_cast<PowerUpType>(rand() % 3); // Random power-up type
    powerUps.emplace_back(type, x, y);
}

void Game::addToArsenal(PowerUpType powerUpType) {
    arsenal.push_back(powerUpType); // Add power-up to arsenal
}

const std::vector<PowerUpType>& Game::getArsenal() const {
    return arsenal;
}

void Game::usePowerUp(PowerUpType powerUpType) {
    auto it = std::find(arsenal.begin(), arsenal.end(), powerUpType);
    if (it != arsenal.end()) {
        applyPowerUp(powerUpType);
        arsenal.erase(it);
        std::cout << "Activated a power-up"<< std::endl;
    }
    else {
        std::cout << "Power-up not available in arsenal!" << std::endl;
    }
}

void Game::applyPowerUp(PowerUpType type) {
    switch (type) {
    case PowerUpType::HomingMissile:
        homingMissileActive = true;
        // Apply homing missile effect
        break;
    case PowerUpType::Gigantification:
        gigantificationActive = true;
        player->scale(2.0f, 2.0f); // Increase player size
        for (Missile* missile : playerMissiles) {
            missile->scale(2.0f, 2.0f); // Increase missile size
        }
        break;
    case PowerUpType::RapidFire:
        rapidFireActive = true;
        player->setAttackSpeed(0.1f); // Increase attack speed
        break;
    }
}

void Game::revertPowerUpEffects() {
    if (homingMissileActive) {
        homingMissileActive = false;
        // Revert homing missile effect
    }
    if (gigantificationActive) {
        gigantificationActive = false;
        player->scale(0.5f, 0.5f); // Revert player size
        for (Missile* missile : playerMissiles) {
            missile->scale(0.5f, 0.5f); // Revert missile size
        }
    }
    if (rapidFireActive) {
        rapidFireActive = false;
        player->setAttackSpeed(0.3f);
    }
}

bool Game::isGameOver() {
    return player->getHearts() <= 0;
}
void Game::renderGameOver() {
    glColor4f(1.0f, 1.0f, 1.0f, textAlpha);
    std::stringstream gameOverStream;
    gameOverStream << "Game Over";
    std::string gameOverText = gameOverStream.str();
    const char* text = gameOverText.c_str();
    void* font = GLUT_BITMAP_HELVETICA_18;
    glRasterPos2f(-0.1f, 0.0f);
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if (textAlpha < 1.0f) {
        textAlpha += textFadeSpeed;  // Gradually increase alpha
        glutPostRedisplay();
    }
}