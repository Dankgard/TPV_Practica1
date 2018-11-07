#pragma once

#include <iostream>
#include "Block.h"
#include "checkML.h"

typedef unsigned int uint;

class BlocksMap {
private:
	Block*** blocks = nullptr;
	uint mapW = 0;
	uint mapH = 0;
	uint rows;
	uint columns;
	uint x;
	uint y;
	Texture* blockTexture = nullptr;

public:
	BlocksMap();
	BlocksMap(uint mapW, uint mapH, Texture* blockTexture);
	~BlocksMap();
	void loadMap(string filename, Texture* texture);
	void render() const;
	uint blockNumber() const;
	SDL_Rect* getDestRect();
	Block* BlocksMap::collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector);
	Block* BlocksMap::blockAt(const Vector2D& p);
	void ballHitsBlock(Block* block);
};
