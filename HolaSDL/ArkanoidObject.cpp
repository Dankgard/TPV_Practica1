#include <iostream>
#include "ArkanoidObject.h"
#include "checkML.h"

ArkanoidObject::ArkanoidObject() :
	pos(), w(), h(), texture() {}

ArkanoidObject::ArkanoidObject(Vector2D pos, uint w, uint h, Texture* t) :
	pos(pos), w(w), h(h), texture(t) {}

void ArkanoidObject::render()
{
	SDL_Rect destRect = getDestRect();
	texture->render(destRect, SDL_FLIP_NONE);
}

SDL_Rect ArkanoidObject::getDestRect()
{
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	return destRect;
}

void ArkanoidObject::loadFromFile()
{

}

void ArkanoidObject::saveToFile() const
{

}

