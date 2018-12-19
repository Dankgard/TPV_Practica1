#include "MainMenuState.h"

MainMenuState::MainMenuState(SdlApplication* app): GameState(app)
{
	ButtonPlay = new MenuButton(app->getTexture(0), 100, 100, 100, 100, startGame, app);
	cout << app;
	gameObjects.push_back(ButtonPlay);
}

void MainMenuState::startGame(SdlApplication* app)
{
	app->getStateMachine()->pushState(new PlayState(app));
}

/*void MainMenuState::handleEvents(SDL_Event even) {
	while (SDL_PollEvent(&even) && !exit)
	{
		ButtonPlay->handleEvents(even);
	}
}*/

void MainMenuState::render() {
	ButtonPlay->render();

	SDL_Rect dstRect;
	dstRect.x = 400;
	dstRect.y = 400;
	dstRect.w = 300;
	dstRect.h = 100;
	Texture* texture = app->getTexture(3);
	texture->render(dstRect, SDL_FLIP_NONE);
}


