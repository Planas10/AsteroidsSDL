#pragma once

#include "Scene.h"
#include "Spaceship.h"
#include "BigAsteroid.h"
#include "MediumAsteroid.h"
#include "SmallAsteroid.h"
#include "Bullet.h"
#include "UIText.h"

using namespace std;

enum GameplayState {ALIVE, DEAD};

class GameplayScene : public Scene {



public:
	GameplayScene()
		: Scene() {}

	void OnStart(SDL_Renderer* rend) override;
	void Update(float dt) override;

private:
	Spaceship* spaceship;
	UIText* scoreText;
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