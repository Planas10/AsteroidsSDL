#pragma once

#include "Scene.h"
#include "UIText.h"

class CreditsScene : public Scene {

public:
	CreditsScene()
		: Scene() {}
	void OnStart(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend);
};