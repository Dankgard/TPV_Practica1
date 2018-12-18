#include "PlayState.h"

const string PlayState::sPlayID = "PLAY";

PlayState::PlayState(SdlApplication* app): GameState(app)
{

};

PlayState::~PlayState()
{

}

void PlayState::update()
{
	GameState::update();
}

void PlayState::render()
{
	GameState::render();
}

void PlayState::handleEvents(SDL_Event event)
{
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {

		}
		else
		{
			GameState::handleEvents(event);
		}
	}
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