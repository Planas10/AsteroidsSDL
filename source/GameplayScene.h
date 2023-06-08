#pragma once

#include "Scene.h"
#include "Spaceship.h"
#include "BigAsteroid.h"
#include "MediumAsteroid.h"
#include "SmallAsteroid.h"
#include "Bullet.h"
#include "UIText.h"
#include <SDL.h>
#include <SDL_mixer.h>


using namespace std;

enum GameplayState {ALIVE, DEAD};

class GameplayScene : public Scene {



public:
	GameplayScene()
		: Scene() {}

	void OnStart(SDL_Renderer* rend) override;
	void Update(float dt) override;

	Mix_Chunk* Laser;
	Mix_Chunk* next_level;
	Mix_Chunk* asteroid;
	Mix_Music* gameplay_music;
	Mix_Chunk* muerte;
	Mix_Chunk* game_over;

private:
	Spaceship* spaceship;
	UIText* scoreText;
	UIText* exitText;
	SDL_Renderer* rend;
	int rounds = 0;

	GameplayState currentState;
	int lives;
	int score = 0;
	float currentStateTime;
	const float stateTimeThreshold = 3.0f;

	void DestroySpaceShip();
	void RespawnSpaceShip();

	//void UpdateScore();
};