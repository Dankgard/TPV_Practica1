#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

typedef unsigned int uint;

class Block {
private:
	Vector2D pos;
	uint w = 0;
	uint h = 0;
	uint color = 0;
	uint row = 0;
	uint col = 0;
	Texture* texture = nullptr;

public:
	Block();
	Block(uint w, uint h, uint color, uint row, uint col, Vector2D pos, Texture* t);
	~Block() {}
	uint getColor() { return color; }
	void render() const;
	uint getX() { return pos.getX(); }
	uint getY() { return pos.getY(); }
	uint getW() { return w; }
	uint getH() { return h; }
};
