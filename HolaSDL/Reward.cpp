#include <iostream>
#include "checkML.h"
#include "Reward.h"
#include "Game.h"

Reward::Reward(Vector2D pos, uint w, uint h, uint tipo, Vector2D vel, Paddle* p, Texture* t, Game* g, list<ArkanoidObject*>::iterator it):
	MovingObject(pos,w,h,t,vel)
{
	type = tipo;
	paddle = p;
	game = g;
	itList = it;
}

void Reward::update()
{
	if (getY() > WIN_HEIGHT)
		deleteReward();
	else
		pos = pos + speed;

	collides();
}

bool Reward::collides()
{
	bool collide = false;
	if (SDL_HasIntersection(&getDestRect(), &paddle->getDestRect()) && !used) {
		used = true;
		kindHelp();
	}
	return collide;
}


void Reward::deleteReward()
{
	game->killObject(index);
}

void Reward::kindHelp()
{
	switch (type)
	{
	case 0:
		game->nextLevel();
		break;
	case 1:
		paddle->longerPaddle();
		break;
	case 3:
		paddle->shorterPaddle();
		break;
	case 4:
		game->extraLife();
		break;
	}
	game->killObject(index);
}

void Reward::render()
{	
	if (getTimeElapsed() >= animVel) {
		animFrame++;
		ticks = 0;
		if (animFrame == 7) {
			animFrame = 0;
		}
	}
	renderFrame(type, animFrame);
}

void Reward::handleEvents(SDL_Event event)
{

}

uint Reward::getTimeElapsed()
{
	return SDL_GetTicks() - ticks;
}
