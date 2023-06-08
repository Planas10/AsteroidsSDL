#include "MenuScene.h"

bool canDoMusic= false;

void MenuScene::OnStart(SDL_Renderer* rend) {
	Scene::OnStart(rend);
	uiObjects.push_back(new UIImage(rend,
		Vector2(250, 250), 0.0f, Vector2(0.4f, 0.4f),
		"resources/logo.png",
		GAME_WIDTH, GAME_HEIGHT, Vector2(20,160)));
	uiObjects.push_back(new UIText(rend,
		Vector2(200, 50), 0.0f, Vector2(1, 1),
		"Sylveon",
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

	Mix_VolumeMusic(30);
	if (!canDoMusic)
	{
		musicaMenu = Mix_LoadMUS("resources/Menu_Music.mp3");
		// Reproducir música en bucle
		Mix_PlayMusic(musicaMenu, -1);
		canDoMusic = true;
	}
}

void MenuScene::Update(float dt) {

	Scene::Update(dt);

	if (IM.GetKeyState(SDLK_1, DOWN)) {
		// Transition code
		finished = true;
		targetScene = "Gameplay";

		canDoMusic = false;
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