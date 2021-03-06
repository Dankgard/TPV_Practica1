#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() {
	
}

GameStateMachine::~GameStateMachine() {

}


GameState* GameStateMachine::getCurrentState() {
	return currentState;
}

void GameStateMachine::pushState(GameState *state)
{
	stateStack.push(state);
	currentState = stateStack.top();
	cout << "Cargado" << currentState << endl;
}

void GameStateMachine::popState()
{
	if (!stateStack.empty())
	{
		delete stateStack.top();
		stateStack.pop();
		currentState = stateStack.top();
	}
}

void GameStateMachine::changeState(GameState *state)
{
	popState();
	pushState(state);	
	currentState = stateStack.top();	
}
