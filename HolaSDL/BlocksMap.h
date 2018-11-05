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
	uint cellW = 0;
	uint cellH = 0;
	

public:
	BlocksMap();
	BlocksMap(uint mapW, uint mapH, uint cellW, uint cellH);
	~BlocksMap();
	void loadMap(string filename, Texture* texture);
	void render() const;
	uint blockNumber() const;
	Block* BlocksMap::collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector);
	Block* BlocksMap::blockAt(const Vector2D& p);
	void ballHitsBlock(Block* block);
};
