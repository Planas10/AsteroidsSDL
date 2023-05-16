#pragma once

#include "Asteroid.h"

class SmallAsteroid : public Asteroid {

public:
	SmallAsteroid(SDL_Renderer* rend, Vector2 pos)
		: Asteroid(rend) {

		int random = rand() % 3;

		switch (random)
		{
		case 0:
			width = 19;
			height = 18;
			padding = Vector2(128.0f, 1.0f);
			break;
		case 1:
			width = 19;
			height = 21;
			padding = Vector2(128.0f, 22.0f);
			break;
		case 2:
			width = 21;
			height = 18;
			padding = Vector2(166.0f, 105.0f);
			break;
		}

		position = pos;
		velocity = CalculatePositionInRadius(110);
		angularVelocity = 110 - (rand() % 221); //Entre -110 i 110

		radius = CalculateRadius(width, height);
	}
};