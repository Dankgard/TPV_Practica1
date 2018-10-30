#include "Wall.h"
#include <iostream>
#include "checkML.h"

Wall::Wall(): pos(), w(), h(), texture() {}

Wall::Wall(uint w, uint h, Vector2D pos, Texture* t) :
	w(w), h(h), pos(pos), texture(t) {}

SDL_Rect* Wall::getDestRect() {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	return &destRect;
}

void Wall::render() const
{
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	texture->render(destRect, SDL_FLIP_NONE);
}