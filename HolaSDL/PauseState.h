#pragma once

#include "GameState.h"
#include "checkML.h"
#include "MenuButton.h"
#include "PlayState.h"

class PauseState :public GameState
{
protected:
	MenuButton* MenuPlay;
	MenuButton* GamePlay;
public:
	PauseState(SdlApplication* app);
	~PauseState();

	
	void render();
	static void MenuGame(SdlApplication* app);
	static void PlayGame(SdlApplication* app);
	
};
