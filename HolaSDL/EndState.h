#pragma once

#include "GameState.h"
#include "MenuButton.h"
#include "checkML.h"
#include <iostream>

class EndState : public GameState {
	protected:

	public:
		EndState(SdlApplication* app);
		~EndState() { }

		void update();
		void render();
		void handleEvents();


};
