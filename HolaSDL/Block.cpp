#include "Block.h"
#include <iostream>
#include "checkML.h"

Block::Block() : ArkanoidObject() {}

Block::Block(uint w, uint h, uint color, uint row, uint col, Vector2D pos, Texture* t) :
	ArkanoidObject(pos, w, h, t), color(color), row(row), col(col) {}


void Block::update()
{

}

bool Block::handleEvents(SDL_Event& event)
{
	return true;
}

// renderiza los bloques
void Block::render() const
{
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;

	uint r, c;
	switch (color)
	{
	case 1:
		r = 0;
		c = 0;
		break;
	case 2:
		r = 0;
		c = 1;
		break;
	case 3:
		r = 0;
		c = 2;
		break;
	case 4:
		r = 1;
		c = 0;
		break;
	case 5:
		r = 1;
		c = 1;
		break;
	case 6:
		r = 1;
		c = 2;
		break;
	}
	if(color!=0)
		texture->renderFrame(destRect, r, c, 0, SDL_FLIP_NONE);
}