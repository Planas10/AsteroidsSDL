#pragma once

#include "InputManager.h"
#include "GameObject.h"
#include <SDL.h>
#include <SDL_mixer.h>

class Spaceship : public GameObject {

private:
	bool canShot;
	bool wantsToShot;

	float lastShotTime;
	float maxShotTime;

	void UpdateMovement(float dt) override;
	void UpdateShot(float dt);
	bool canDoSpaceshipMusic;
	Mix_Chunk* soundEffect;

public:
	Spaceship(SDL_Renderer* renderer, Vector2 pos, float rot, Vector2 scl);
	bool BulletShooted();
	void Update(float dt) override;
	void PlatSoundEffect();
};




