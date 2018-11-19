#include <iostream>
#include "ArkanoidObject.h"
#include "checkML.h"

ArkanoidObject::ArkanoidObject(Vector2D pos, uint w, uint h, Texture* t) :
	pos(pos), w(w), h(h), texture(t) {}

/*virtual void ArkanoidObject::render() const;
{
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	texture->render(destRect, SDL_FLIP_NONE);
}*/