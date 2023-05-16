#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Utils.h"
#include "Vector2.h"

class GameObject {

protected:
	//FLAGS
	bool pendingDestroy = false;

	// TRANSFORM
	Vector2 position;
	float rotation;
	Vector2 scale;

	// RENDER INFORMATION
	SDL_Texture* texture;
	int width;
	int height;
	Vector2 padding;

	// PHYSICS MOVEMENT
	Vector2 velocity;
	float angularVelocity;

	Vector2 acceleration;
	float angularAcceleration;

	float linearDrag;
	float angularDrag;

	float accelerationFactor;
	float angularAccelerationFactor;

	float radius;

	virtual void UpdateMovement(float dt);
	virtual void ClampPosition();

public:
	GameObject(SDL_Renderer* renderer, int w, int h, Vector2 pad);
	~GameObject();
	virtual void Update(float dt);
	virtual void Render(SDL_Renderer* renderer);
	virtual void Destroy() { pendingDestroy = true; }
	bool IsPendingDestroy() { return pendingDestroy; }
	Vector2 GetPosition() { return position; }
	float GetAngle() { return rotation * (M_PI / 180.0f); }
	Vector2 GetVelocity() { return velocity; }
	float GetRadius() { return radius * (scale.x > scale.y ? scale.x : scale.y); }
};