#include "Paddle.h"
#include <iostream>
#include "checkML.h"
#include "Game.h"

Paddle::Paddle() : MovingObject() {}

Paddle::Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t) :
	MovingObject(pos, w, h, t, Vector2D(speed.getX(),speed.getY())){
}


void Paddle::update()
{
	if (powered && getTimeElapsed() >= originalTime)
	{
		originalPaddle();
	}
}


// mueve la pala
void Paddle::mov(int speed){
	if (pos.getX() >= 20-speed && pos.getX()<=780-w-speed)
		pos = Vector2D(pos.getX() + speed, pos.getY());
}


// maneja los eventos de teclado de la pala
void Paddle::handleEvent(SDL_Event event) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:			
			mov(-speed.getX());
			break;
		case SDLK_RIGHT:			
			mov(speed.getX());			
			break;
		default:
			break;
		}
	}
}
bool Paddle::handleEvents(SDL_Event& event) {
	return true;
}

bool Paddle::collides(const SDL_Rect* rect, Vector2D& collVector)
{
	bool collide = false;
	if (SDL_HasIntersection(rect, &getDestRect())) {
		SDL_Rect* paddlerect = &getDestRect();
		int middleX = paddlerect->x + (paddlerect->w / 2);
		if (rect->x < middleX)
			collVector = Vector2D(0.15, 1);
		else if (rect->x > middleX)
			collVector = Vector2D(-0.15, 1);
		else
			collVector = Vector2D(0, 1);
		collide = true;
	}
	return collide;
}
void Paddle::Wsave() {
	oldW = w;
}

void Paddle::shorterPaddle()
{
	Wsave();
	w = oldW - 40;
	powered = true;
	powerupTicks = SDL_GetTicks();
}

void Paddle::longerPaddle()
{
	Wsave();
	w = oldW + 40;
	powered = true;
	powerupTicks = SDL_GetTicks();
}

void Paddle::originalPaddle()
{
	w = oldW;
	powered = false;
	powerupTicks = 0;
}

uint Paddle::getTimeElapsed()
{
	return SDL_GetTicks() - powerupTicks;
}

void Paddle::saveToFile(ofstream& file)
{
	w = oldW;
	MovingObject::saveToFile(file);	
}


void Paddle::loadFromFile(ifstream& file)
{
	MovingObject::loadFromFile(file);
	oldW = w;
}
