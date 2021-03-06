#include <iostream>
#include "checkML.h"
#include "Reward.h"
#include "PlayState.h"

Reward::Reward(Vector2D pos, uint w, uint h, uint tipo, Vector2D vel, Paddle* p, Texture* t, PlayState* g, list<ArkanoidObject*>::iterator it):
	MovingObject(pos,w,h,t,vel)
{
	type = tipo;
	paddle = p;
	game = g;
	itList = it;
	TimeAnima = SDL_GetTicks();
}

void Reward::update()
{
	collides();

	if (getY() > SDL_WIN_HEIGHT)
		deleteReward();
	else
		pos = pos + speed;
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
	game->killObject(this);
}

void Reward::kindHelp()
{
	switch (type)
	{
	case 0: // L
		game->nextLevel();		
		break;
	case 1: // E
		paddle->longerPaddle();		
		break;
	case 3: // S
		paddle->shorterPaddle();		
		break;
	case 4: // R
		game->extraLife();		
		break;
	}
	game->killObject(this);
}

void Reward::render()
{	
	if (SDL_GetTicks() > TimeAnima + animVel) {
		animFrame++;
		TimeAnima = SDL_GetTicks();
		if (animFrame == 8) {
			animFrame = 0;
		}
	}
	renderFrame(type, animFrame);
}

void Reward::handleEvents(SDL_Event event)
{

}
bool Reward::handleEvents(SDL_Event& event) {
	return true;
}

uint Reward::getTimeElapsed()
{
	return SDL_GetTicks() - ticks;
}
