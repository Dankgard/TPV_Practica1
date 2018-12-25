#pragma once

#include "GameState.h"
#include "MenuButton.h"
#include "checkML.h"
#include <iostream>
#include "PlayState.h"


class EndState : public GameState {
	protected:
		MenuButton* MenuPlay;
		MenuButton* GamePlay;
		MenuButton* LoadPlay;
	public:
		EndState(SdlApplication* app);
		~EndState();

		void update();
		void render();
		void handleEvents();

		static void MenuGame(SdlApplication* app);
		static void PlayGame(SdlApplication* app);
		static void LoadGame(SdlApplication* app);
};
