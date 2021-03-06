#pragma once

#include "GameState.h"
#include <stack>
#include "checkML.h"

using namespace std;

class GameStateMachine
{
protected:	
	stack<GameState*> stateStack;
	GameState* currentState = nullptr;	
public:
	GameStateMachine();
	~GameStateMachine();

	GameState* getCurrentState();
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
};
