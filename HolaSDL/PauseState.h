#pragma once

#include "GameState.h"
#include "checkML.h"

class PauseState :public GameState
{
public:
	PauseState();
	~PauseState();

	void update();
	void render();
	void handleEvent();
};
