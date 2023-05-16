#include "InputManager.h"

void InputManager::Listen() {
	
	// Update Pressed and Released keys from previous frame
	for (std::unordered_map<Sint32, KeyState>::iterator it = keys.begin(); it != keys.end(); it++) {
		
		if (it->second == DOWN)
			it->second = HOLD;

		if (it->second == UP) {
			it->second = EMPTY;
		}
	}

	// Read mouse coords
	SDL_GetMouseState(&mouseX, &mouseY);

	// Process input for this event
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				if (keys[e.key.keysym.sym] == HOLD) {
					break;
				}
				keys[e.key.keysym.sym] = DOWN;
				break;

			case SDL_KEYUP:
				keys[e.key.keysym.sym] = UP;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
					leftClick = true;
				break;

			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT)
					leftClick = false;
				break;
		}
	}
}