#include "MenuScene.h"

void MenuScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
	uiObjects.push_back(new UIImage(rend,
		Vector2(250, 250), 0.0f, Vector2(0.8f, 0.8f),
		"resources/sylveon.png",
		GAME_WIDTH, GAME_HEIGHT, Vector2(20,20)));
	uiObjects.push_back(new UIText(rend,
		Vector2(250, 50), 0.0f, Vector2(1, 1),
		"Vaporeon",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));
}

void MenuScene::Update(float dt) {

	Scene::Update(dt);

	if (IM.GetKeyState(SDLK_1, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "Gameplay";
	}
	
	if (IM.GetKeyState(SDLK_2, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "Highscores";
	}
}