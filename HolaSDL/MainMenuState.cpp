#include "MainMenuState.h"

MainMenuState::MainMenuState(SdlApplication* app): GameState(app)
{
	ButtonPlay = new MenuButton(app->getTexture(playt), 200, 425, 100, 100, startGame, app);
	CargarPlay = new MenuButton(app->getTexture(loadt), 500, 425, 100, 100, loadGame, app);
	cout << app;
	gameObjects.push_back(ButtonPlay);
	gameObjects.push_back(CargarPlay);
}

MainMenuState::~MainMenuState()
{
	delete ButtonPlay;
	delete CargarPlay;
}


void MainMenuState::startGame(SdlApplication* app)
{
	app->getStateMachine()->pushState(new PlayState(app));
}

void MainMenuState::loadGame(SdlApplication* app)
{
	string loadCode;
	cout << "Introduzca la partida guardada: " << loadCode;
	cin >> loadCode;
	app->getStateMachine()->pushState(new PlayState(app, loadCode));
}

/*void MainMenuState::handleEvents(SDL_Event even) {
	while (SDL_PollEvent(&even) && !exit)
	{
		ButtonPlay->handleEvents(even);
	}
}*/

void MainMenuState::render() {
	ButtonPlay->render();
	CargarPlay->render();

	SDL_Rect dstRect;
	dstRect.x = 100;
	dstRect.y = 50;
	dstRect.w = 700;
	dstRect.h = 200;
	Texture* texture = app->getTexture(titlet);
	texture->render(dstRect, SDL_FLIP_NONE);
}


