#include "HighscoresScene.h"
#include <algorithm>
#include <vector>

using namespace std;

void HighscoresScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
	uiObjects.push_back(new UIText(rend,
		Vector2(250, 50), 0.0f, Vector2(1, 1),
		"HighScores",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));

	//crear fun per introduir la score, que els textos estiguin ja en el file posats i no s'hagin de tornar a escriure
	//podem provar de fer servir el getline com a la practica del bomversus

	ofstream archivoEntrada("resources/datos.txt", ofstream::trunc);
	if (!archivoEntrada) {
		cerr << "No se pudo abrir el archivo de entrada.\n";
		return;
	}
	archivoEntrada << "1st_____________;" << endl;
	archivoEntrada << "2nd_____________;" << endl;
	archivoEntrada << "3rd_____________;" << endl;
	archivoEntrada << "4th_____________;" << endl;
	archivoEntrada << "5th_____________;" << endl;
	archivoEntrada.close();
	
	

	//sort(scores.begin(), scores.end(), [](const string& a, const string& b) {
	//	return stoi(a) > stoi(b);
	//});

	int x_pos = 150;
	int y_pos = 150;
	string temp;

	for (size_t i = 0; i < 5; i++)
	{
		ifstream archivoEntrada("resources/datos.txt");
		getline(archivoEntrada, temp, ';');

		uiObjects.push_back(new UIText(
			rend,
			Vector2(x_pos, y_pos),
			0.0f,
			Vector2(1, 1),
			temp,
			"resources/Hyperspace.ttf",
			{ 0xFF, 0xFF, 0x00, 0xFF }
		));
		y_pos += 50;
		cout << temp << endl;
		getline(archivoEntrada, temp);
	}
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
		"Credits",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }
	));
}

void HighscoresScene::Update(float dt) {

	Scene::Update(dt);

	if (IM.GetKeyState(SDLK_3, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "Credits";
	}

	if (IM.GetKeyState(SDLK_SPACE, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "MainMenu";
	}
}

void HighscoresScene::Render(SDL_Renderer* rend) {
	
	Scene::Render(rend);
	
	//cout << "Highscore" << endl;
}