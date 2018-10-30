#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"
#include "Texture.h";
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"

using namespace std;

typedef unsigned int uint;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 5;
const uint FRAME_RATE = 0;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer * renderer = nullptr;
	Ball* ball = nullptr;
	BlocksMap* blocksmap = nullptr;
	Wall* rightwall = nullptr;
	Wall* leftwall = nullptr;
	Wall* topwall = nullptr;
	Paddle* paddle = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];

public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	bool collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector);
};
