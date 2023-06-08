#include "GameplayScene.h"
#include "MenuScene.h"




void GameplayScene::OnStart(SDL_Renderer* rend) {

	Laser = Mix_LoadWAV("resources/Laser_Shoot.wav");
	next_level = Mix_LoadWAV("resources/next_level.wav");
	asteroid = Mix_LoadWAV("resources/Destroy_Asteroids.wav");
	muerte = Mix_LoadWAV("resources/muerte.wav");
	game_over = Mix_LoadWAV("resources/game_over.wav");
	gameplay_music = Mix_LoadMUS("resources/AmongUs_Remix.mp3");

	currentState = GameplayState::ALIVE;
	currentStateTime = 0.0f;
	lives = 3;

	this->rend = rend;

	score = 0;

	Scene::OnStart(rend);

	RespawnSpaceShip();
	
	gameObjects.push_back(new BigAsteroid(rend, 100.0f));

	scoreText = new UIText(
		rend,
		Vector2(30, 30),
		0.0f,
		Vector2(1, 1),
		"SCORE: 0",
		"resources/Hyperspace.ttf",
		{ 0xFF, 0xFF, 0x00, 0xFF }
	);
	uiObjects.push_back(scoreText);

	// Inicializar SDL y SDL Mixer
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	// Reproducir música en bucle
	Mix_PlayMusic(gameplay_music, -1);

	Mix_VolumeMusic(30);
	Mix_Volume(-1, 15);
	Mix_Volume(0, 15);
	Mix_Volume(1, 15);
	Mix_Volume(2, 15);
	Mix_Volume(3, 30);
}


void GameplayScene::Update(float dt) {

	string scoretext = to_string(score);
	string Score = "Score:" + scoretext;
	scoreText->ChangeText(Score);

	currentStateTime += dt;

	cout << Score << endl;


	// CHECK IF THERE ARE ASTEROIDS
	int asteroids = 0;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
		// CAST GAMEOBJECT TO ASTEROID
		if (Asteroid* a = dynamic_cast<Asteroid*>(*it)) {
			asteroids++;
		}
	}

	if (asteroids == 0) {
		rounds++;

		// Reproducir efecto de sonido una vez
		Mix_PlayChannel(2, next_level, 0);

		for (int i = 0; i < rounds + 2; i++) {
			gameObjects.push_back(new BigAsteroid(rend, 100.0f));
		}
	}

	// SPAWNERS
	if (spaceship != nullptr) {
		if (spaceship->BulletShooted()) {

			// Reproducir efecto de sonido una vez
			Mix_PlayChannel(1, Laser, 0);

			gameObjects.push_back(new Bullet(rend, spaceship->GetPosition(), spaceship->GetAngle(), 640.0f));


			//Mix_FreeChunk(soundEffect);
		}

	}

	for (int i = 0; i < gameObjects.size(); i++) {
		// CAST GAMEOBJECT TO ASTEROID
		if (Asteroid* a = dynamic_cast<BigAsteroid*>(gameObjects[i])) {
			// CHECK IF ASTEROID HAS TO BE DESTROYED
			if (a->IsPendingDestroy()) {

				// Reproducir efecto de sonido una vez
				Mix_PlayChannel(1, asteroid, 0);

				gameObjects.push_back(new MediumAsteroid(rend, a->GetPosition()));
				gameObjects.push_back(new MediumAsteroid(rend, a->GetPosition()));

				//Add points to score
				score += 50;
			}
		}
		if (Asteroid* a = dynamic_cast<MediumAsteroid*>(gameObjects[i])) {
			if (a->IsPendingDestroy()) {

				// Reproducir efecto de sonido una vez
				Mix_PlayChannel(0, asteroid, 0);

				gameObjects.push_back(new SmallAsteroid(rend, a->GetPosition()));
				gameObjects.push_back(new SmallAsteroid(rend, a->GetPosition()));

				//Add points to score
				score += 30;
			}
		}
	}

	// DESTROYERS
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
		// CAST GAMEOBJECT TO BULLET
		if (Bullet* b = dynamic_cast<Bullet*>(*it)) {
			// CHECK IF BULLET HAS TO BE DESTROYED
			if (b->IsPendingDestroy())
				b->Destroy();
		}
	}

	Scene::Update(dt);

	// COLLISIONS

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
		// CAST GAMEOBJECT TO BULLET
		if (Bullet* b = dynamic_cast<Bullet*>(*it)) {
			// CHECK IF A BULLET HAS COLLIDED WITH AN ASTEROID
				// DESTROY BULLET
				// DESTROY ASTEROID
			for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
				if (Asteroid* a = dynamic_cast<Asteroid*>(*it)) {
					Vector2 bulletToAsteroid = a->GetPosition() - b->GetPosition();
					float distanceSquared = bulletToAsteroid.x * bulletToAsteroid.x + bulletToAsteroid.y * bulletToAsteroid.y;
					float squareRadiusSum = a->GetRadius() + b->GetRadius();				// bulletRadius + asteroidRadius
					squareRadiusSum *= squareRadiusSum;

					if (distanceSquared < squareRadiusSum) {

						// Reproducir efecto de sonido una vez
						Mix_PlayChannel(0, asteroid, 0);

						b->Destroy();
						a->Destroy();
					}
				}
				
			}
		}
	}

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
		// CAST GAMEOBJECT TO ASTEROID
		if (Asteroid* a = dynamic_cast<Asteroid*>(*it)) {
			// CHECK IF ASTEROID HAS COLLIDED WITH SPACESHIP
				// DESTROY ASTEROID
				// DESTROY SPACESHIP
			if (spaceship != nullptr && currentStateTime > stateTimeThreshold) {
				Vector2 spaceshiptToAsteroid = a->GetPosition() - spaceship->GetPosition();
				float distanceSquared = spaceshiptToAsteroid.x * spaceshiptToAsteroid.x + spaceshiptToAsteroid.y * spaceshiptToAsteroid.y;
				float squareRadiusSum = a->GetRadius() * 0.5f + spaceship->GetRadius() * 0.5f;		// playerRadius + asteroidRadius
				squareRadiusSum *= squareRadiusSum;

				if (distanceSquared < squareRadiusSum) {

					// Reproducir efecto de sonido una vez
					Mix_PlayChannel(-1, muerte, 0);

					a->Destroy();
					DestroySpaceShip();
				}
			}
		}
	}

	if (currentState == GameplayState::DEAD && currentStateTime > stateTimeThreshold)
	{
		if (lives != 0) {
			RespawnSpaceShip();
		}
		else {
			Mix_HaltMusic();

			finished = true;
			targetScene = "MainMenu";
		}
	}
	else
	{
		if (lives == 0)
		{
			Mix_HaltMusic();

			// Reproducir efecto de sonido una vez
			Mix_PlayChannel(-1, game_over, 0);
		}
	}
}

void GameplayScene::RespawnSpaceShip() {
	spaceship = new Spaceship(rend, Vector2(GAME_WIDTH / 2, GAME_HEIGHT / 2), 0.0f, Vector2(1.f, 1.f));
	gameObjects.push_back(spaceship);

	currentState = GameplayState::ALIVE;
	currentStateTime = 0.0f;
}
void GameplayScene::DestroySpaceShip(){
	spaceship->Destroy();
	spaceship = nullptr;

	currentState = GameplayState::DEAD;
	currentStateTime = 0.0f;

	lives--;
	// UPDATE UI

}