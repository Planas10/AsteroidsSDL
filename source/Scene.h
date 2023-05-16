#pragma once

#include <SDL.h>
#include <string>
#include <vector>

#include "InputManager.h"
#include "GameObject.h"
#include "UIObject.h"

class Scene {

protected:
	std::vector<GameObject*> gameObjects;
	std::vector<UIObject*> uiObjects;

	bool finished = false;
	std::string targetScene;

public:
	Scene() = default;
	bool isFinnished() { return finished; }
	std::string GetTargetScene() { return targetScene; }
	virtual void OnStart(SDL_Renderer* rend) {
		finished = false;
	}
	virtual void Update(float dt) {

		for (int i = gameObjects.size() - 1; i >= 0; i--) {
			if (gameObjects[i]->IsPendingDestroy()) {
				delete gameObjects[i];
				gameObjects.erase(gameObjects.begin() + i);
			}
		}

		for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
			(* it)->Update(dt);

		for (auto it = uiObjects.begin(); it != uiObjects.end(); it++)
			(*it)->Update(dt);
	}
	virtual void Render(SDL_Renderer* rend) {
		for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
			(* it)->Render(rend);

		for (auto it = uiObjects.begin(); it != uiObjects.end(); it++)
			(*it)->Render(rend);
	}
	virtual void OnExit() {
		for (int i = gameObjects.size() - 1; i >= 0; i--) {
			delete gameObjects[i];
		}
		for (int i = uiObjects.size() - 1; i >= 0; i--) {
			delete uiObjects[i];
		}

		gameObjects.clear();
		uiObjects.clear();
	}
};