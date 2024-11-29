#include "Controller.h"

bool Controller::mapKey(unsigned char key, bool isPressed)
{
    switch (key) {
    case 'w':
	case 'W':
        keyStates[MovementKey::W] = isPressed;
        return true;
    case 'a':
	case 'A':
        keyStates[MovementKey::A] = isPressed;
        return true;
    case 's':
	case 'S':
        keyStates[MovementKey::S] = isPressed;
        return true;
    case 'd':
	case 'D':
        keyStates[MovementKey::D] = isPressed;
        return true;
    default:
        return false;
    }
}

std::string Controller::keyToString(MovementKey key) const
{
    switch (key) {
    case MovementKey::W: return "W";
    case MovementKey::A: return "A";
    case MovementKey::S: return "S";
    case MovementKey::D: return "D";
    default: return "Unknown";
    }
}

Controller::Controller() : debugMode(true) {
    // Initialize all keys to "not pressed"
    keyStates[MovementKey::W] = false;
    keyStates[MovementKey::A] = false;
    keyStates[MovementKey::S] = false;
    keyStates[MovementKey::D] = false;
}

Controller::~Controller()
{
}

void Controller::setDebugMode(bool enable)
{
    debugMode = enable;
}

void Controller::keyDown(unsigned char key)
{
    if (mapKey(key, true) && debugMode) {
        std::cout << "Key " << key << " pressed." << std::endl;
    }
}

void Controller::keyUp(unsigned char key)
{
    if (mapKey(key, false) && debugMode) {
        std::cout << "Key " << key << " released." << std::endl;
    }
}

bool Controller::isKeyPressed(MovementKey key) const
{
    auto it = keyStates.find(key);
    return it != keyStates.end() ? it->second : false;
}

void Controller::printKeyStates() const
{
    if (!debugMode) return;
    
	for (auto it = keyStates.begin(); it != keyStates.end(); ++it) {
		std::cout << keyToString(it->first) << ": " << (it->second ? "pressed" : "not pressed") << std::endl;
	}
}
