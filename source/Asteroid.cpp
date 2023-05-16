#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer* rend)
	: GameObject(rend, 0, 0, Vector2()) {

	// CALCULATE RADIUS
	float spawnRadius = CalculateRadius(GAME_WIDTH, GAME_HEIGHT);
	
	// CALCULATE POSITION IN PERIMETER WITH A GIVEN RADIUS (h)
	Vector2 perimeterPosition = CalculatePositionInRadius(spawnRadius);

	// CLAMP TO RECTANGLE
	float halfHeight = GAME_HEIGHT / 2.0f + (float)radius;
	float halfWidth = GAME_WIDTH / 2.0f + (float)radius;

	perimeterPosition = ClampPositionToRectangle(perimeterPosition, halfWidth, halfHeight);

	// TRANSFORM
	position = perimeterPosition;
	position = position + Vector2(halfWidth, halfHeight);
	rotation = rand() % 360;
	scale = Vector2(1.0f, 1.0f);

	// PHYSICS
	acceleration = Vector2(0.0f, 0.0f);
	angularAcceleration = 0.0f;
	linearDrag = 0.0f;
	angularDrag = 0.0f;

	velocity = Vector2();
	angularVelocity = 0.0f;
}