#include "UIText.h"

void UIText::Render(SDL_Renderer* rend) {

	SDL_Rect dest;
	dest.x = position.x;// - (int)((float)width * scale.x / 2.0f);
	dest.y = position.y;// - (int)((float)height * scale.y / 2.0f);
	dest.w = (float)width * scale.x;
	dest.h = (float)height * scale.y;

	SDL_RenderCopyEx(rend, texture,
		NULL, &dest,
		rotation,
		NULL,				
		SDL_FLIP_NONE);		
}

void UIText::GenerateTexture(SDL_Renderer* rend) {

	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 28);

	if (font == nullptr) {
		std::cout << "[!] Error loading font family: " << SDL_GetError();
	}

	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);

	if (surf == nullptr) {
		std::cout << "[!] Error loading texture: " << SDL_GetError();
	}

	texture = SDL_CreateTextureFromSurface(rend, surf);

	if (texture == nullptr) {
		std::cout << "[!] Error generating texture: " << SDL_GetError();
	}

	width = surf->w;
	height = surf->h;

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
}