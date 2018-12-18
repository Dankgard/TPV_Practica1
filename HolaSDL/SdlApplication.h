#pragma once

#include "GameStateMachine.h"
#include "Texture.h"
#include <iostream>
#include "checkML.h"

using uint = unsigned int;

class  SdlApplication{
protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const uint WIN_WIDTH = 800;
	const uint WIN_HEIGHT = 600;

	bool exit = false;
	Texture* textures[6];
	GameStateMachine* state = nullptr;
	enum GameState { menu, play, pause, end };

public:
	SdlApplication();
	~SdlApplication();

	void run();
	void render();
	void handleEvents();

	GameStateMachine* getStateMachine();
};
