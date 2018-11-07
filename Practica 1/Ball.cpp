#include "Ball.h"
#include <iostream>
#include "checkML.h"
#include "Game.h"

Ball::Ball() : pos(), w(), h(), speed(), texture(), game() {}

Ball::Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t, Game* g) :
	pos(pos), w(w), h(h), speed(speed), texture(t), game(g){}

// devuelve el SDL_Rect de la pelota
SDL_Rect Ball::getDestRect() {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	return destRect;
}

// renderiza la pelota
void Ball::render() const
{	
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	texture->render(destRect, SDL_FLIP_NONE);
}

// actualiza el estado de la pelota
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

	if(pos.getY() > WIN_HEIGHT) {
		game->death();
	}
}

// devuelve la pelota a su estado original al empezar un nivel
void Ball::resetBall(Vector2D originalPos,double speedX, double speedY) {
	speed = Vector2D(-speedX, speedY);
	pos = originalPos;
}