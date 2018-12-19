#include "MainMenuState.h"
#include "SdlApplication.h"

MainMenuState::MainMenuState(SdlApplication* app): GameState(app)
{
	ButtonPlay = new MenuButton(app->getTexture(0), 100, 100, 100, 100, startGame, app);
	gameObjects.push_back(ButtonPlay);
}

void MainMenuState::startGame(SdlApplication* app)
{
	app->getStateMachine()->pushState(new PlayState(app));
}

void MainMenuState::handleEvents(SDL_Event even) {
	while (SDL_PollEvent(&even) && !exit)
	{
		ButtonPlay->handleEvents(even);
	}
}

void MainMenuState::render() {
	ButtonPlay->render();
}


