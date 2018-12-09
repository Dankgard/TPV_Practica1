#pragma once

#include "GameState.h"

class GameState;
class GameStateMachine
{
private:	
	stack<GameState*> stack;
	std::vector<GameState*> machineGameStates;
	bool exit;
public:
	void update();
	void render();
	void handleEvents();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();	
};