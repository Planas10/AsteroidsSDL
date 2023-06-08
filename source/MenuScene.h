#pragma once

#include "Scene.h"
#include "UIImage.h"
#include "UIText.h"
#include "Utils.h"
#include <SDL.h>
#include <SDL_mixer.h>

class MenuScene : public Scene {

public:
	MenuScene()
		: Scene() {}
	void OnStart(SDL_Renderer* rend) override;
	void Update(float dt) override;

	Mix_Music* musicaMenu;
};