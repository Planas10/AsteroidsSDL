#pragma once

#include "Scene.h"
#include "UIText.h"

class HighscoresScene : public Scene {

public:
	HighscoresScene()
		: Scene() {}
	void OnStart(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend);
	void OnExit() override;
};