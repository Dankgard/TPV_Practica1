#include "EndState.h"

EndState::EndState(SdlApplication* app) : GameState(app) {
	cout << app;
	MenuPlay = new MenuButton(app->getTexture(exitt), 200, 425, 100, 100, MenuGame, app);
	GamePlay = new MenuButton(app->getTexture(playt), 350, 425, 100, 100, PlayGame, app);
	LoadPlay = new MenuButton(app->getTexture(loadt), 500, 425, 100, 100, LoadGame, app);
	gameObjects.push_back(MenuPlay);
	gameObjects.push_back(GamePlay);
	gameObjects.push_back(LoadPlay);
};

EndState::~EndState() {
	delete MenuPlay;
	delete GamePlay;
	delete LoadPlay;
}


void EndState::update() {
	GameState::update();
}

void EndState::render() {
	MenuPlay->render();
	GamePlay->render();
	LoadPlay->render();

	SDL_Rect dstRect;
	dstRect.x = 300;
	dstRect.y = 50;
	dstRect.w = 200;
	dstRect.h = 200;
	Texture* texture = app->getTexture(gameovert);
	texture->render(dstRect, SDL_FLIP_NONE);
}

void EndState::handleEvents() {

}

void EndState::MenuGame(SdlApplication* app) {
	app->getStateMachine()->popState();
	app->getStateMachine()->popState();
	//app->getStateMachine()->pushState(new MainMenuState(app));
}
void EndState::PlayGame(SdlApplication* app) {
	app->getStateMachine()->popState();
	app->getStateMachine()->popState();
	app->getStateMachine()->pushState(new PlayState(app));
}

void EndState::LoadGame(SdlApplication* app) {
	app->getStateMachine()->popState();
	app->getStateMachine()->popState();
	string loadCode;
	cout << "Introduzca la partida guardada: " << loadCode;
	cin >> loadCode;
	app->getStateMachine()->pushState(new PlayState(app, loadCode));
}

