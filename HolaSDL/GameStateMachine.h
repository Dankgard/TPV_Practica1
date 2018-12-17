#pragma once

#include "GameState.h"
#include <stack>
#include "checkML.h"


class GameState;
class GameStateMachine
{
private:	
	stack<GameState*> stateStack;
	GameState* currentState = nullptr;
	bool exit;
public:
	GameStateMachine();
	~GameStateMachine();

	GameState* getCurrentState();
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();	
};