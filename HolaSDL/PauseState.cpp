#include "PauseState.h"

PauseState::PauseState(SdlApplication* app) : GameState(app) {
	cout << app;
	MenuPlay = new MenuButton(app->getTexture(playt), 200, 425, 100, 100, MenuGame, app);
	GamePlay = new MenuButton(app->getTexture(loadt), 500, 425, 100, 100, PlayGame, app);
	gameObjects.push_back(MenuPlay);
	gameObjects.push_back(GamePlay);
};

PauseState::~PauseState() {
	delete MenuPlay;
	delete GamePlay;
}

void PauseState::render() {
	MenuPlay->render();
	GamePlay->render();
	
	SDL_Rect dstRect;
	dstRect.x = 300;
	dstRect.y = 50;
	dstRect.w = 200;
	dstRect.h = 200;
	Texture* texture = app->getTexture(pauset);
	texture->render(dstRect, SDL_FLIP_NONE);
}
void PauseState::MenuGame(SdlApplication* app) {
	app->getStateMachine()->pushState(new MainMenuState(app));
}
void PauseState::PlayGame(SdlApplication* app) {
	app->getStateMachine()->pushState(new PlayState(app));
}

