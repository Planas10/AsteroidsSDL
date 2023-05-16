#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, int w, int h, Vector2 pad) 
	: width(w), height(h), padding(pad) {

	position = Vector2();
	rotation = 0.0f;
	scale = Vector2(1, 1);

	// Load texture
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");

	if (surf == nullptr) {
		std::cout << "[!] Error loading texture: " << SDL_GetError();
	}

	// Generate texture
	texture = SDL_CreateTextureFromSurface(renderer, surf);

	if (texture == nullptr) {
		std::cout << "[!] Error generating texture: " << SDL_GetError();
	}

	// Deleting surface
	SDL_FreeSurface(surf);

	radius = CalculateRadius(width, height);
}

GameObject::~GameObject() {
	SDL_DestroyTexture(texture);
}

void GameObject::Update(float dt) {
	UpdateMovement(dt);
	ClampPosition();
}

void GameObject::ClampPosition() {

	float scaledWidth = float(width) * scale.x;
	float scaledHeight = float(height) * scale.y;

	int biggestAxis = scaledWidth > scaledHeight ? scaledWidth : scaledHeight;

	if (position.x > GAME_WIDTH + biggestAxis)
		position.x -= (GAME_WIDTH + biggestAxis * 2);

	if (position.x < 0.0f - biggestAxis)
		position.x += (GAME_WIDTH + biggestAxis * 2);

	if (position.y > GAME_HEIGHT + biggestAxis)
		position.y -= (GAME_HEIGHT + biggestAxis * 2);

	if (position.y < 0.0f - biggestAxis)
		position.y += (GAME_HEIGHT + biggestAxis * 2);
}

void GameObject::UpdateMovement(float dt) {

	// UPDATE VELOCITY AND ANGULAR VELOCITY
	velocity = velocity + acceleration * dt;
	angularVelocity = angularVelocity + angularAcceleration * dt;

	// DRAG
	velocity = velocity * (1.0f - linearDrag * dt);
	angularVelocity = angularVelocity * (1.0f - angularDrag * dt);

	// UPDATE POSITION AND ROTATION
	position = position + velocity * dt;			//Units: pixels/s
	rotation = rotation + angularVelocity * dt;
}

void GameObject::Render(SDL_Renderer* rend) {

	SDL_Rect source;
	source.x = padding.x;
	source.y = padding.y;
	source.w = width;
	source.h = height;

	SDL_Rect dest;
	dest.x = position.x - (int)((float)source.w * scale.x / 2.0f);
	dest.y = position.y - (int)((float)source.h * scale.y / 2.0f);
	dest.w = (float)source.w * scale.x;
	dest.h = (float)source.h * scale.y;

	SDL_RenderCopyEx(rend, texture,
		&source, &dest,
		90.0f + rotation,
		NULL,				// Rotation point: NULL = center
		SDL_FLIP_NONE);		// Don't flip image
}