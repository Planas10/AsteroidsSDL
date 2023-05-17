#include "HighscoresScene.h"
#include <algorithm>
#include <vector>

void HighscoresScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
}

std::vector<std::string> scores;


void HighscoresScene::OnStart(SDL_Renderer* rend) {
	uiObjects.push_back(new UIText(rend,
		Vector2(250, 50), 0.0f, Vector2(1, 1),
		"High Score",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));
	/*
	std::ifstream archivoEntrada("resources/datos.txt");
	if (!archivoEntrada) {
		std::cerr << "No se pudo abrir el archivo de entrada.\n";
		return 1;
	}
	archivoEntrada >> scores; 
	archivoEntrada.close(); 
	*/
	

	std::sort(scores.begin(), scores.end(), [](const std::string& a, const std::string& b) {
		return std::stoi(a) > std::stoi(b);
	});

	uiObjects.push_back(new UIText(rend,
		Vector2(250, 50), 0.0f, Vector2(1, 1),
		scores,
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));

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