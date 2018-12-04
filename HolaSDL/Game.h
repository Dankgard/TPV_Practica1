#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"
#include "Texture.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Reward.h"
#include <list>
#include <fstream>

using namespace std;

typedef unsigned int uint;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 6;
const uint FRAME_RATE = 10;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

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
	Texture* textures[NUM_TEXTURES];
	string nombre[NUM_TEXTURES] = { "ball.png","paddle.png","side.png","topside.png", "bricks.png","rewards.png" };
	enum TextureType { balltexture,  paddletexture, sidetexture, topsidetexture, brickstexture, rewardtexture };
	uint currentLevel = 0;
	string levels[3] = { "level01.ark", "level02.ark", "level03.ark" };
	uint powerUpType[4] = { 0, 1, 3, 4 };
	list<ArkanoidObject*> arkanoidObjects;

	string saveFile;

public:
	Game();
	Game(string filename);
	~Game();
	void run();
	void render();
	void handleEvents();
	void update();
	bool collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector);
	void death();
	void nextLevel();
	void extraLife();
	void killObject(uint ind);
	void loadList();
	void saveGame();
	void spawnReward(Vector2D pos);
};
