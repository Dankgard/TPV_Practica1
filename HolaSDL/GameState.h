#pragma once

#include "GameObject.h"
#include "SDL.h"
#include "checkML.h"
#include <list>

using namespace std;

class SdlApplication;
class GameState {
protected:
	list<GameObject*> gameObjects;
	SdlApplication* app;
public:
	GameState(SdlApplication* app) {};
	~GameState() { }

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event event);

};