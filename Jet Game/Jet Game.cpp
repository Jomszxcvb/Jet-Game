#define GLEW_STATIC // <----- define GLEW_STATIC

#include <iostream>
#include <vector>
#include <algorithm> // For std::remove_if

#include <GL/glew.h> // <----- additional header files
#include <GL/glut.h>

#include "Controller.h"
#include "Player.h"
#include "Missile.h"

void display();
void update(int value);

Player* player;
Controller controller;
std::vector<Missile*> missiles;
float missileTimer = 0.0f; // Timer for missile creation


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Jet Game");

	glewInit(); // <----- initialize GLEW

	player = new Player();

	glutDisplayFunc(display);
	glutTimerFunc(1000 / 60, update, 0);

	glutKeyboardFunc([](unsigned char key, int x, int y) {
		controller.keyDown(key);
		});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		controller.keyUp(key);
		});

	glutMainLoop();

	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	player->render();

	for (Missile* missile : missiles) {
		missile->render();
	}

	glFlush();
}

void update(int value)
{
	if (controller.isKeyPressed(MovementKey::W)) {
		player->update(true, false, false, false, 0.01f);
	}
	if (controller.isKeyPressed(MovementKey::S)) {
		player->update(false, true, false, false, 0.01f);
	}
	if (controller.isKeyPressed(MovementKey::A)) {
		player->update(false, false, true, false, 0.01f);
	}
	if (controller.isKeyPressed(MovementKey::D)) {
		player->update(false, false, false, true, 0.01f);
	}


	// Update missile timer
	missileTimer += 0.016f; // Assuming update is called every 16ms (60 FPS)

	// Create a new missile at the player's position every 0.3 seconds
	if (missileTimer >= 0.3f) {
		missiles.push_back(new Missile(player->getX(), player->getY(), 0.01f));
		missileTimer = 0.0f; // Reset timer
	}

	for (Missile*& missile : missiles) {
		missile->update(0.01f);
		if (missile->isOutOfBound()) {
			delete missile;
			missile = nullptr;
		}
	}

	// Remove nullptr entries from the missiles vector
	missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [](Missile* missile) { return missile == nullptr; }), missiles.end());

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}


