#pragma once

#include "GameObject.h"

class Bullet : public GameObject {

protected:
	float lifeTime;

	void Update(float dt) override;
	void UpdateLifetime(float dt);

public:
	Bullet(SDL_Renderer* renderer, Vector2 pos, float angle, float velocityFactor);
};