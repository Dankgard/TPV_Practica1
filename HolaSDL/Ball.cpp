#include "Ball.h"
#include <iostream>
#include "checkML.h"
#include "Game.h"

Ball::Ball() : pos(), w(), h(), speed(), texture(), game() {}

Ball::Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t, Game* g) :
	pos(pos), w(w), h(h), speed(speed), texture(t), game(g){}

SDL_Rect Ball::getDestRect() {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	return destRect;
}

void Ball::render() const
{	
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	texture->render(destRect, SDL_FLIP_NONE);
}
void Ball::update() {
	Vector2D prevPos = pos;
	pos = prevPos + speed;
	Vector2D collVector;
	SDL_Rect ballRect = getDestRect();
	if (game->collides(&ballRect, &speed, collVector))
	{
		speed = speed - (collVector * (2 * (speed*collVector)));
		pos = prevPos + speed;
	}
}