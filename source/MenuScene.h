#pragma once

#include "Scene.h"
#include "UIImage.h"
#include "UIText.h"
#include "Utils.h"

class MenuScene : public Scene {

public:
	MenuScene()
		: Scene() {}
	void OnStart(SDL_Renderer* rend) override;
	void Update(float dt) override;

};