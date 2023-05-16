#include "GameplayScene.h"

void GameplayScene::OnStart(SDL_Renderer* rend) {
	
	currentState = GameplayState::ALIVE;
	currentStateTime = 0.0f;
	lives = 3;

	this->rend = rend;

	Scene::OnStart(rend);

	RespawnSpaceShip();
	
	gameObjects.push_back(new BigAsteroid(rend, 100.0f));
}

void GameplayScene::Update(float dt) {

	currentStateTime += dt;

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
		for (int i = 0; i < rounds + 2; i++) {
			gameObjects.push_back(new BigAsteroid(rend, 100.0f));
		}
	}

	// SPAWNERS
	if (spaceship != nullptr) {
		if (spaceship->BulletShooted())
			gameObjects.push_back(new Bullet(rend, spaceship->GetPosition(), spaceship->GetAngle(), 640.0f));
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		// CAST GAMEOBJECT TO ASTEROID
		if (Asteroid* a = dynamic_cast<BigAsteroid*>(gameObjects[i])) {
			// CHECK IF ASTEROID HAS TO BE DESTROYED
			if (a->IsPendingDestroy()) {
				gameObjects.push_back(new MediumAsteroid(rend, a->GetPosition()));
				gameObjects.push_back(new MediumAsteroid(rend, a->GetPosition()));
			}
		}
		if (Asteroid* a = dynamic_cast<MediumAsteroid*>(gameObjects[i])) {
			if (a->IsPendingDestroy()) {
				gameObjects.push_back(new SmallAsteroid(rend, a->GetPosition()));
				gameObjects.push_back(new SmallAsteroid(rend, a->GetPosition()));
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
			finished = true;
			targetScene = "MainMenu";
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