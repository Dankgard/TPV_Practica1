#include "PlayState.h"

const std::string PlayState::sPlayID = "PLAY";

void PlayState::update()
{
	// nothing for now
}

void PlayState::render()
{
	// nothing for now
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