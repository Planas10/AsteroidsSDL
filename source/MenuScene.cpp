#include "MenuScene.h"

bool canDoMusic = true;

void MenuScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
	uiObjects.push_back(new UIImage(rend,
		Vector2(250, 250), 0.0f, Vector2(0.8f, 0.8f),
		"resources/sylveon.png",
		GAME_WIDTH, GAME_HEIGHT, Vector2(20,20)));
	uiObjects.push_back(new UIText(rend,
		Vector2(200, 50), 0.0f, Vector2(1, 1),
		"Vaporeon",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }));
	uiObjects.push_back(new UIText(
		rend,
		Vector2(100, 460),
		0.0f,
		Vector2(1, 1),
		"HighScore",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }
	));
	uiObjects.push_back(new UIText(
		rend,
		Vector2(300, 460),
		0.0f,
		Vector2(1, 1),
		"Credits",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }
	));


	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);


	if (canDoMusic)
	{
		// Cargar música
		Mix_Music* music = Mix_LoadMUS("resources/Menu_Music.mp3");
		canDoMusic = false;
		// Reproducir música en bucle
		Mix_PlayMusic(music, -1);

		// Cambiar el volumen a la mitad (rango: 0 - 128)
		Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
	}
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

	if (IM.GetKeyState(SDLK_3, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "Credits";
	}
}