#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, Vector2 pos, float angle, float velocityFactor) 
	: GameObject(renderer, 7, 8, Vector2(33, 31)) {


	Vector2 bulletSpawn = pos + (Vector2(cos(angle), sin(angle)) * 20);		// PlayerRadius
	position = bulletSpawn;

	velocity = Vector2(cos(angle), sin(angle)) * velocityFactor;
	angularVelocity = 0.0f;

	acceleration = Vector2();
	angularAcceleration = 0.0f;

	linearDrag = 0.3f;
	angularDrag = 0.0f;

	accelerationFactor = 0.0f;						//Px/sec^2
	angularAccelerationFactor = 0.0f;				//Deg(graus)/sec^2

	lifeTime = 0.8f;
}

void Bullet::Update(float dt) {

	GameObject::Update(dt);
	UpdateLifetime(dt);
}

void Bullet::UpdateLifetime(float dt) {

	lifeTime -= dt;

	if (lifeTime <= 0.0f)
		Destroy();
}