#include "PauseState.h"

PauseState::PauseState(SdlApplication* app) : GameState(app) {
	cout << app;
	MenuPlay = new MenuButton(app->getTexture(1), 500, 10, 100, 100, MenuGame, app);
	GamePlay = new MenuButton(app->getTexture(0), 10, 10, 100, 100, PlayGame, app);
	gameObjects.push_back(MenuPlay);
	gameObjects.push_back(GamePlay);
};

PauseState::~PauseState() {

}

void PauseState::render() {
	GameState::render();
}
void PauseState::MenuGame(SdlApplication* app) {
	app->getStateMachine()->pushState(new MainMenuState(app));
}
void PauseState::PlayGame(SdlApplication* app) {
	app->getStateMachine()->pushState(new PlayState(app));
}

