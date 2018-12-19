#pragma once

#include "GameState.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "checkML.h"
#include <iostream>
#include "SDLApplication.h"


class PlayState : public GameState
{
public:
	PlayState(SdlApplication* app);
	~PlayState();	

	void render();
	bool handleEvents(SDL_Event& event);	
};
