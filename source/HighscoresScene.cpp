#include "HighscoresScene.h"
#include <algorithm>
#include <vector>



void HighscoresScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
	uiObjects.push_back(new UIText(rend,
		Vector2(250, 50), 0.0f, Vector2(1, 1),
		"High Score",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));

	//crear fun per introduir la score, que els textos estiguin ja en el file posats i no s'hagin de tornar a escriure
	//podem provar de fer servir el getline com a la practica del bomversus

	std::ofstream archivoEntrada("resources/datos.txt", std::ofstream::trunc);
	if (!archivoEntrada) {
		std::cerr << "No se pudo abrir el archivo de entrada.\n";
		return;
	}
	archivoEntrada << "Mamawebasso digo glu glu glu glu" << std::endl;
	archivoEntrada << "malpario tripleijueputa" << std::endl;
	archivoEntrada.close(); 
	
	

	//std::sort(scores.begin(), scores.end(), [](const std::string& a, const std::string& b) {
	//	return std::stoi(a) > std::stoi(b);
	//});

	//uiObjects.push_back(new UIText(rend,
	//	Vector2(250, 50), 0.0f,
	//	Vector2(1, 1),scores,
	//	"resources/Hyperspace.ttf",
	//	{ 0xFF, 0xFF, 0x00, 0xFF }));

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