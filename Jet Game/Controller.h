#pragma once
#include <iostream>
#include <unordered_map>

enum class InputKey {
	W,
	A,
	S,
	D,
	_1,
	_2,
};

class Controller
{
private:
	std::unordered_map<InputKey, bool> keyStates;
	bool debugMode; // Debug mode flag

	// Map keyboard input to MovementKey and update its state
	bool mapKey(unsigned char key, bool isPressed);

	// Convert enum to string for debugging
	std::string keyToString(InputKey key) const;

public:
	Controller();
	~Controller();

	// Enable or disable debug mode
	void setDebugMode(bool enable);

	// Handle key press event
	void keyDown(unsigned char key);

	// Handle key release event
	void keyUp(unsigned char key);

	// Check if a specific movement key is pressed
	bool isKeyPressed(InputKey key) const;

	// Debug function to print all key states
	void printKeyStates() const;
};

