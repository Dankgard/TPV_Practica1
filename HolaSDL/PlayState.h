#pragma once

#include "GameState.h"
#include "Vector2D.h"
#include "Texture.h"

using namespace std;

class Game;
class PlayState : public GameState
{
private:
	static const string sPlayID;
public:
	PlayState();
	~PlayState();	

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event event);

	virtual bool onEnter();
	virtual bool onExit();

	virtual string getStateID() const { return sPlayID; }
};
