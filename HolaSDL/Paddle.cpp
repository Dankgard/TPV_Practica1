#include "Paddle.h"
#include <iostream>
#include "checkML.h"
#include "Game.h"

Paddle::Paddle() : MovingObject() {}

Paddle::Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t) :
	MovingObject(pos, w, h, t, Vector2D(0,0)){}


// mueve la pala
void Paddle::mov(int speed){
	if (pos.getX() >= 20-speed && pos.getX()<=780-w-speed)
		pos = Vector2D(pos.getX() + speed, pos.getY());
}


// maneja los eventos de teclado de la pala
void Paddle::handleEvents(SDL_Event event) {
	
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

bool Paddle::collides(const SDL_Rect* rect, Vector2D& collVector)
{
	bool collide = true;
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
}
