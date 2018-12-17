#pragma once

#include "GameState.h"
#include "PauseState.h"
#include "SdlApplication.h"
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"


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
