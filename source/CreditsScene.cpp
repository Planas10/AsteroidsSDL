#include "CreditsScene.h"
#include <algorithm>
#include <vector>

using namespace std;

void CreditsScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);

	string creator1 = "Marc Planas";
	string creator2 = "Xavier Massaneda";

	//Titol
	uiObjects.push_back(new UIText(
		rend,
		Vector2(200, 50),
		0.0f,
		Vector2(1, 1),
		"Credits",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));

	uiObjects.push_back(new UIText(
		rend,
		Vector2(160, 150),
		0.0f,
		Vector2(1, 1),
		creator1,
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));

	uiObjects.push_back(new UIText(
		rend,
		Vector2(130, 200),
		0.0f,
		Vector2(1, 1),
		creator2,
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));
	uiObjects.push_back(new UIText(
		rend,
		Vector2(100, 450),
		0.0f,
		Vector2(1, 1),
		"Main Menu",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }
	));
	uiObjects.push_back(new UIText(
		rend,
		Vector2(300, 450),
		0.0f,
		Vector2(1, 1),
		"HighScore",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }
	));

}

void CreditsScene::Update(float dt) {

	Scene::Update(dt);
	if (IM.GetKeyState(SDLK_2, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "Highscores";
	}
	if (IM.GetKeyState(SDLK_SPACE, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "MainMenu";
	}
}

void CreditsScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

	//cout << "Highscore" << endl;
}