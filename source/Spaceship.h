#pragma once

#include "InputManager.h"
#include "GameObject.h"

class Spaceship : public GameObject {

private:
	bool canShot;
	bool wantsToShot;

	float lastShotTime;
	float maxShotTime;

	void UpdateMovement(float dt) override;
	void UpdateShot(float dt);

public:
	Spaceship(SDL_Renderer* renderer, Vector2 pos, float rot, Vector2 scl);
	bool BulletShooted();
	void Update(float dt) override;
};



