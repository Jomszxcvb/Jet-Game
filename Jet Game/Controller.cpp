#include "Controller.h"

bool Controller::mapKey(unsigned char key, bool isPressed)
{
    switch (key) {
    case 'w':
	case 'W':
        keyStates[InputKey::W] = isPressed;
        return true;
    case 'a':
	case 'A':
        keyStates[InputKey::A] = isPressed;
        return true;
    case 's':
	case 'S':
        keyStates[InputKey::S] = isPressed;
        return true;
    case 'd':
	case 'D':
        keyStates[InputKey::D] = isPressed;
        return true;
	case '1':
		keyStates[InputKey::_1] = isPressed;
		return true;
	case '2':
		keyStates[InputKey::_2] = isPressed;
    default:
        return false;
    }
}

std::string Controller::keyToString(InputKey key) const
{
    switch (key) {
    case InputKey::W: return "W";
    case InputKey::A: return "A";
    case InputKey::S: return "S";
    case InputKey::D: return "D";
	case InputKey::_1: return "1";
	case InputKey::_2: return "2";
    default: return "Unknown";
    }
}

Controller::Controller() : debugMode(true) {
    // Initialize all keys to "not pressed"
    keyStates[InputKey::W] = false;
    keyStates[InputKey::A] = false;
    keyStates[InputKey::S] = false;
    keyStates[InputKey::D] = false;
	keyStates[InputKey::_1] = false;
	keyStates[InputKey::_2] = false;
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

bool Controller::isKeyPressed(InputKey key) const
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
