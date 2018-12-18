#pragma once

#include"GameState.h"
#include "checkML.h"
#include "MenuButton.h"

using namespace std;

class MainMenuState : public GameState 
{
	protected:
		MenuButton* ButtonPlay;
	public:
		MainMenuState(SdlApplication* app);
		~MainMenuState();

		void handleEvents();
};