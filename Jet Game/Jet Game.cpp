#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

int main(int argc, char** argv) {
    Game game;
    game.init(argc, argv);
    return 0;
}
