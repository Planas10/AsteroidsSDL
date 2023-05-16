#pragma once

#include <stdlib.h>
#include <cmath>
#include <math.h>

#include "Vector2.h"

#define GAME_WIDTH 500
#define GAME_HEIGHT 500
#define M_PI 3.14159265358979323846

inline float CalculateRadius(int width, int height) {

	float a = ((float)width / 2.0f);
	a *= a;		// Power of two
	float b = ((float)height / 2.0f);
	b *= b;

	// RADIUS
	float h = sqrt(a + b);

	return h;
}

inline Vector2 CalculatePositionInRadius(float r) {
	
	Vector2 permiterPosition;

	float angle = rand() % 360;
	angle *= M_PI / 180;		//DEG TO RAD

	permiterPosition.x = cos(angle) * r;
	permiterPosition.y = sin(angle) * r;

	return permiterPosition;
}

inline Vector2 ClampPositionToRectangle(Vector2 pos, float halfWidth, float halfHeight) {

	if (pos.y < -halfHeight)	// TOP CLAMP
		pos.y = -halfHeight;

	if (pos.y > halfHeight)		// BOTTOM CLAMP
		pos.y = halfHeight;

	if (pos.x < -halfWidth)		// LEFT CLAMP
		pos.x = -halfWidth;

	if (pos.x > halfWidth)		// RIGHT CLAMP
		pos.x = halfWidth;

	return pos;
}

inline bool CheckPointInsideCenteredRectangle(Vector2 point, Vector2 rectCenter, int w, int h) {

	float distX = abs(point.x - rectCenter.x);
	float distY = abs(point.y - rectCenter.y);

	bool insideX = distX < (float)w / 2.0f;
	bool insideY = distY < (float)h / 2.0f;

	return insideX && insideY;
}