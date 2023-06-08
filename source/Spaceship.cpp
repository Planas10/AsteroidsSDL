#include "Spaceship.h"


Spaceship::Spaceship(SDL_Renderer* renderer, Vector2 pos, float rot, Vector2 scl) 
	: GameObject(renderer, 31, 39, Vector2(0,0)) {
	movement = Mix_LoadWAV("resources/movement.wav");

	position = pos;
	rotation = rot;
	scale = scl;

	velocity = Vector2();
	angularVelocity = 0.0f;

	acceleration = Vector2();
	angularAcceleration = 0.0f;

	linearDrag = 1.2f;
	angularDrag = 6.0f;

	accelerationFactor = 100.0f;					// pxs	/ s^2
	angularAccelerationFactor = 500.0f * 45.f;	// degs	/ s^2

	canShot = false;
	wantsToShot = false;

	maxShotTime = 0.25f;
	lastShotTime = maxShotTime;
}

void Spaceship::Update(float dt) {

	GameObject::Update(dt);
	UpdateShot(dt);
}

void Spaceship::PlatSoundEffect()
{
	if (canDoSpaceshipMusic)
	{
		canDoSpaceshipMusic = false;

		// Reproducir efecto de sonido una vez
		Mix_PlayChannel(3, movement, 0);

	}

}

void Spaceship::UpdateMovement(float dt) {

	acceleration = Vector2();

	if (IM.GetKeyState(SDLK_UP, DOWN) || IM.GetKeyState(SDLK_UP, HOLD)) {
		Vector2 dir;
		float rotationInRadians = rotation * (M_PI / 180.0f);
		dir.x = cos(rotationInRadians);
		dir.y = sin(rotationInRadians);
		PlatSoundEffect();
		acceleration = dir * accelerationFactor;
	}else if(IM.GetKeyState(SDLK_UP, UP) || IM.GetKeyState(SDLK_DOWN, UP))
	{
		Mix_HaltChannel(3);
		canDoSpaceshipMusic = true;

	}
		

	// Cargar efecto de sonido

	angularAcceleration = 0.0f;

	if (IM.GetKeyState(SDLK_LEFT, DOWN) || IM.GetKeyState(SDLK_LEFT, HOLD)) {
	
		angularAcceleration = dt * -angularAccelerationFactor;
	}
	else if (IM.GetKeyState(SDLK_RIGHT, DOWN) || IM.GetKeyState(SDLK_RIGHT, HOLD)) {
		//PlatSoundEffect();
		angularAcceleration = dt * angularAccelerationFactor;
	}
	

	GameObject::UpdateMovement(dt);
}

void Spaceship::UpdateShot(float dt) {

	// Update Time
	lastShotTime += dt;

	// Can Shoot
	canShot = lastShotTime >= maxShotTime;

	// Wants to Shot
	wantsToShot = IM.GetKeyState(SDLK_SPACE, DOWN) || IM.GetKeyState(SDLK_SPACE, HOLD);
}

bool Spaceship::BulletShooted() {

	if (canShot && wantsToShot) {
		lastShotTime = 0.0f;
		return true;
	}

	return false;
}