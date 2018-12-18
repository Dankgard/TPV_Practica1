#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Block: public ArkanoidObject {
private:
	uint color = 0;
	uint row = 0;
	uint col = 0;

public:
	Block();
	Block(uint w, uint h, uint color, uint row, uint col, Vector2D pos, Texture* t);
	~Block() {}

	virtual void update();
	virtual bool handleEvents(SDL_Event& event);

	uint getColor() { return color; }
	void setColor(uint col) { color = col; }
	void render() const;
};
