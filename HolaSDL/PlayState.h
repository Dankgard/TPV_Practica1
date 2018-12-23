#pragma once

#include "GameState.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "checkML.h"
#include <iostream>
#include "SDLApplication.h"
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Texture.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Reward.h"
#include <list>
#include <fstream>

using namespace std;
const uint SDL_FRAME_RATE = 10;


class PlayState : public GameState
{
private:
	Ball* ball = nullptr;
	BlocksMap * blocksmap = nullptr;
	Wall* rightwall = nullptr;
	Wall* leftwall = nullptr;
	Wall* topwall = nullptr;
	Paddle* paddle = nullptr;
	Reward* reward = nullptr;

	bool exit = false;
	bool win = false;
	bool gameOver = false;
	int lifes = 0;
	bool savedGame = false;

	Vector2D ballpos;
	Vector2D ballspeed;

	uint currentLevel = 0;
	string levels[3] = { "level01.ark", "level02.ark", "level03.ark" };
	uint powerUpType[4] = { 0, 1, 3, 4 };
	list<ArkanoidObject*> arkanoidObjects;

	string saveFile;
public:
	PlayState(SdlApplication* app);
	PlayState(SdlApplication* app, string filename);
	~PlayState();	

	void run();
	void renderExample();
	void render();
	void handleEvents();
	void update();
	bool collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector);
	void death();
	void nextLevel();
	void extraLife();
	void killObject(Reward* r);
	void loadList();
	void saveGame();
	void spawnReward(Vector2D pos);

	bool handleEvents(SDL_Event& event);	
};
