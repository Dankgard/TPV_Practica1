#include "MainMenuState.h"
#include "SdlApplication.h"

MainMenuState::MainMenuState(SdlApplication* app): GameState(app)
{
	ButtonPlay = new MenuButton(app->getTexture(0), 100, 100, 100, 100, startGame);
}

void MainMenuState::startGame(SdlApplication* app)
{
	
}


