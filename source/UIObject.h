#pragma once

#include <SDL.h>

#include "Vector2.h"

class UIObject {

protected:
	Vector2 position;
	float rotation;
	Vector2 scale;

	SDL_Texture* texture;
	int width;
	int height;
	Vector2 padding;

	virtual void GenerateTexture(SDL_Renderer* rend) = 0;

public:
	UIObject(SDL_Renderer* rend, Vector2 pos, float rot, Vector2 scl)
		: position(pos), rotation(rot), scale(scl) {}
	~UIObject() { SDL_DestroyTexture(texture); }
	virtual void Update(float dt) = 0;
	virtual void Render(SDL_Renderer* rend) = 0;
};