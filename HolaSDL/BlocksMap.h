#pragma once

#include <iostream>
#include "Block.h"
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class BlocksMap: public ArkanoidObject {
private:
	Block*** blocks = nullptr;
	uint rows;
	uint columns;

public:
	BlocksMap();
	BlocksMap(uint w, uint h, Texture* t, Vector2D pos);
	~BlocksMap();
	void loadMap(string filename, Texture* texture);
	void render() const;
	uint blockNumber() const;
	Block* BlocksMap::collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector);
	Block* BlocksMap::blockAt(const Vector2D& p);
	void ballHitsBlock(Block* block);
};
