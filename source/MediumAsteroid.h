#pragma once

#include "Asteroid.h"

class MediumAsteroid : public Asteroid {
	
public:
	MediumAsteroid(SDL_Renderer* rend, Vector2 pos)
		: Asteroid(rend) {

		int random = rand() % 2;

		switch (random)
		{
		case 0:
			width = 37;
			height = 36;
			padding = Vector2(41.3f, 3.0f);
			break;
		case 1:
			width = 43;
			height = 38;
			padding = Vector2(81.0f, 2.0f);
			break;
		}

		position = pos;
		velocity = CalculatePositionInRadius(70);
		angularVelocity = 70 - (rand() % 141); //Entre -70 i 70

		radius = CalculateRadius(width, height);
	}
};