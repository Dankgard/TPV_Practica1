#include "Ball.h"
#include <iostream>
#include "checkML.h"

Ball::Ball() : pos(), w(), h(), speed(), texture() {}

Ball::Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t) :
	pos(pos), w(w), h(h), speed(speed), texture(t) {}

void Ball::render()
{	
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	texture->render(destRect, SDL_FLIP_NONE);
}
void Ball::update() {
	Vector2D prevPos = pos;
	pos = prevPos + speed;
}