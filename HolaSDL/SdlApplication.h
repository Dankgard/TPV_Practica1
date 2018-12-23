#pragma once

#include "GameStateMachine.h"
#include "Texture.h"
#include "MainMenuState.h"
#include <iostream>
#include "checkML.h"

const uint SDL_WIN_WIDTH = 800;
const uint SDL_WIN_HEIGHT = 600;
const uint SDL_NUM_TEXTURES = 12;
const enum SDLTextureType { ballt, paddlet, sidet, topsidet, exitt, gameovert, loadt, pauset, playt, titlet, brickst, rewardt };


class  SdlApplication{
protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool exit = false;
	Texture* textures[SDL_NUM_TEXTURES];
	string textureFile[SDL_NUM_TEXTURES] = { "ball.png","paddle.png","side.png","topside.png", "exit.png", "gameover.png", "load.png", "pause.png", "play.png", "title.png", "bricks.png","rewards.png" };
	GameStateMachine* state = nullptr;
	
	enum GameState { menu, play, pause, end };

public:
	SdlApplication();
	~SdlApplication();

	void run();
	void render();
	void handleEvents();
	Texture* getTexture(SDLTextureType type);

	GameStateMachine* getStateMachine();
};