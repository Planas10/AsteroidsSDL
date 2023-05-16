#include "HighscoresScene.h"

void HighscoresScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
}

void HighscoresScene::Update(float dt) {

	Scene::Update(dt);

	if (IM.GetKeyState(SDLK_SPACE, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "MainMenu";
	}
}

void HighscoresScene::Render(SDL_Renderer* rend) {
	
	Scene::Render(rend);
	
	std::cout << "Highscore" << std::endl;
}

void HighscoresScene::OnExit() {

}