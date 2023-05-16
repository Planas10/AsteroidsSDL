#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(SDL_Renderer* rend, Vector2 pos, int vel)
	: Asteroid(rend) {

	Vector2 randomPosition = Vector2(pos.x + (-10 + rand() % 10), pos.y + (-10 + rand() % 10));
	position = randomPosition;
	scale = (scale / 2);

	velocity = velocity + Vector2(rand() % vel, rand() % vel);
}