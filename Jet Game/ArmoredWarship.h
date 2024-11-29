#pragma once
#include <GL/glut.h>

class ArmoredWarship {
public:
    ArmoredWarship();
    void render();

private:
    void warshipBody();
    void warshipWings();
    void warshipSideThrusters();
    void warshipBackThruster();
    void warshipCockpit();
};
