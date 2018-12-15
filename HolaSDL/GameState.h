#pragma once

#include "GameObject.h"
#include "checkML.h"
#include <list>

using namespace std;

class Game;
class GameState {
protected:
	list<GameObject*> gameObjects;
	Game* game;
public:
	GameState();
	~GameState() { }

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvents(SDL_Event event) = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;	

	virtual string getStateID() const = 0;
};