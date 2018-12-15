#include "PlayState.h"

const string PlayState::sPlayID = "PLAY";

PlayState::PlayState()
{

}

PlayState::~PlayState()
{

}

void PlayState::update()
{
	// nothing for now
}

void PlayState::render()
{
	// nothing for now
}

void handleEvents(SDL_Event event)
{

}

bool PlayState::onEnter()
{
	cout << "Entrar PlayState" << endl;
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Salir PlayState" << endl;
	return true;
}