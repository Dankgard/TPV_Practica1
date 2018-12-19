#pragma once

#include"GameState.h"
#include "PlayState.h"
#include "checkML.h"
#include "MenuButton.h"

using namespace std;

using CallBackOnClick = void(SdlApplication* app);

class MainMenuState : public GameState 
{
	protected:
		MenuButton* ButtonPlay;
	public:
		MainMenuState(SdlApplication* app);
		~MainMenuState();

		void render();
		//void handleEvents(SDL_Event e);
		static void startGame(SdlApplication* app);
};