#pragma once

#include <iostream>
#include<string>
#include <SDL_image.h>

#include "UIObject.h"

class UIImage : public UIObject {

protected:
	std::string resourcePath;

	void GenerateTexture(SDL_Renderer* rend) override;

public:
	UIImage(SDL_Renderer* rend, Vector2 pos, float rot, Vector2 scl, std::string path, int w, int h, Vector2 pad)
		: UIObject(rend, pos, rot, scl), resourcePath(path) {
		width = w;
		height = h;
		padding = pad;

		GenerateTexture(rend);
	}
	void Update(float dt) override {}
	void Render(SDL_Renderer* rend) override;
};