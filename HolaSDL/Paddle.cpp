#include "Paddle.h"
#include <iostream>
#include "checkML.h"

Paddle::Paddle() : pos(), w(), h(), speed(), texture() {}

Paddle::Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t) :
	pos(pos), w(w), h(h), speed(speed), texture(t) {}

void Paddle::render() const
{
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	texture->render(destRect, SDL_FLIP_NONE);
}