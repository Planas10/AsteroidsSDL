#pragma once

#include <SDL.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "InputManager.h"
#include "MenuScene.h"
#include "GameplayScene.h"
#include "HighscoresScene.h"
#include "CreditsScene.h"

class GameEngine {
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	void InitSDL();
	void InitWindowAndRenderer(int windowWidth, int windowHeight);

public:
	GameEngine(int windowWidth, int windowHeight);
	void Update();
	void Finish();
};