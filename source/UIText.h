#pragma once

#include <iostream>
#include <string>

#include "SDL_ttf.h"
#include "UIObject.h"

class UIText : public UIObject {

protected:
	std::string text;
	std::string fontPath;
	SDL_Color color;
	SDL_Renderer* renderer;

	void GenerateTexture(SDL_Renderer* rend) override;

public:
	UIText(
		SDL_Renderer* rend,
		Vector2 pos,
		float rot,
		Vector2 scl,
		std::string txt,
		std::string path,
		SDL_Color col
	)
		: UIObject(rend, pos, rot, scl), text(txt), fontPath(path), color(col), renderer(rend) {
		GenerateTexture(rend);
	}
	void Update(float dt) override {}
	void Render(SDL_Renderer* rend) override;
	void ChangeText(std::string newText) {

		SDL_DestroyTexture(texture);
		text = newText;
		GenerateTexture(renderer);
	}
};