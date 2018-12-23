#include "Ball.h"
#include <iostream>
#include "checkML.h"
#include "PlayState.h"

Ball::Ball() : MovingObject(), game() {}

Ball::Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t, PlayState* g) :
	MovingObject(pos, w, h, t, speed), game(g){}


bool Ball::handleEvents(SDL_Event& event)
{
	return true;
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

	if(pos.getY() > SDL_WIN_HEIGHT) {
		game->death();
	}
}

// devuelve la pelota a su estado original al empezar un nivel
void Ball::resetBall(Vector2D originalPos,double speedX, double speedY) {
	speed = Vector2D(-speedX, speedY);
	pos = originalPos;
}
