#include "GameEngine.h"

GameEngine::GameEngine(int windowWidth, int windowHeight) {
	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeight);
}

void GameEngine::InitSDL() {

	// Check if SDL can run --> < 0 if OK
	int result = SDL_Init(SDL_INIT_VIDEO);

	if (result < 0) {
		std::cout << "[!] SDL_Init Error: " << SDL_GetError();
	}

	if (TTF_Init() == -1)
		std::cout << "[!] TTF_Init error: " << SDL_GetError();
}

void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {

	// Create a window
	window = SDL_CreateWindow("Vaporeon",				// Window name
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // Window Position
		windowWidth, windowHeight,						// Window size
		SDL_WINDOW_SHOWN);								// Window flags, shown by default

	// Check if window has created
	if (window == nullptr) {
		std::cout << "[!] Error creating window: " << SDL_GetError();
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Check if renderer has created
	if (renderer == nullptr) {
		std::cout << "[!] Error creating renderer: " << SDL_GetError();
	}
}

void GameEngine::Update() {

	// TIME CONTROL
	float dt = 0;
	float lastTime = (double)SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
	
	const int fps = 60;
	const float frameTime = 1.0f / float(fps);

	// SCENES
	std::unordered_map<std::string, Scene*> gameScenes;
	gameScenes["MainMenu"] = new MenuScene();
	gameScenes["Gameplay"] = new GameplayScene();
	gameScenes["Highscores"] = new HighscoresScene();

	Scene* currentScene = gameScenes["MainMenu"];
	currentScene->OnStart(renderer);

	while (!IM.GetQuit()) {

		// Calculate DeltaTime;
		float currentTime = (double)SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
		dt += currentTime - lastTime;
		lastTime = currentTime;
		
		if (dt > frameTime) {
			//Update input
			IM.Listen();

			// Update Logic
			currentScene->Update(dt);

			// Render
			SDL_RenderClear(renderer);  // Clear Screen
			// SDL_RenderCopyEX(...)	// Render Objects
			currentScene->Render(renderer);
			SDL_RenderPresent(renderer);

			// Scene transition
			if (currentScene->isFinnished()) {
				currentScene->OnExit();
				currentScene = gameScenes[currentScene->GetTargetScene()];
				currentScene->OnStart(renderer);
			}

			// Reset DeltaTime
			dt -= frameTime;
		}
	}

	currentScene->OnExit();

	// Clear all scenes pointers
	for (auto it = gameScenes.begin(); it != gameScenes.end(); it++) {
		delete it->second;
	}
}

void GameEngine::Finish() {

	// Clear dynamic memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}