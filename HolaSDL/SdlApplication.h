#pragma once

#include "GameStateMachine.h"
#include "Texture.h"
#include <iostream>
#include "checkML.h"



class  SdlApplication{
protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int WIN_WIDTH = 800;
	const int WIN_HEIGHT = 600;

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
	Texture* getTexture(int texture);

	GameStateMachine* getStateMachine();
};