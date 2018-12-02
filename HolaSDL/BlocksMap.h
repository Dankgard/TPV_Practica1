#pragma once

#include <iostream>
#include "Block.h"
#include "checkML.h"
#include "ArkanoidObject.h"
//#include "Game.h"

typedef unsigned int uint;

class Game;
class BlocksMap: public ArkanoidObject {
private:
	Block*** blocks;
	uint rows;
	uint columns;
	// probabilidad sobre 100
	uint rewardSpawnProb = 50;

public:
	BlocksMap();
	BlocksMap(uint w, uint h, Texture* t);
	~BlocksMap();
	void update();
	virtual void handleEvents(SDL_Event event);
	void loadMap(string filename, Texture* texture);
	void render();
	uint blockNumber() const;
	Block* collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector);
	Block* blockAt(const Vector2D& p);
	bool collision(const SDL_Rect* rect, const Vector2D* ballVel, Vector2D& collVector, Game* game);
	void ballHitsBlock(Block* block);
};

