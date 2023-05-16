#pragma once

#include <SDL.h>
#include <unordered_map>

#define IM InputManager::Instance()

enum KeyState { EMPTY, DOWN, UP, HOLD };

class InputManager {

private:
	std::unordered_map<Sint32, KeyState> keys;
	int mouseX;
	int mouseY;
	bool leftClick;
	bool quit;

	InputManager() {
		quit = false;
	}
	
public:
	static InputManager& Instance() {
		static InputManager manager;
		return manager;
	}
	InputManager(const InputManager&) = delete;
	InputManager& operator = (const InputManager&) = delete;

	void Listen();		// Event Processor
	bool GetKeyState(Sint32 key, KeyState state) { return keys[key] == state; }	// Acces Key Dictionary and check if State is what is demanding
	int GetMouseX() { return mouseX; }
	int GetMouseY() { return mouseY; }
	bool GetLeftClick() { return leftClick; }
	bool GetQuit() { return quit; }
};