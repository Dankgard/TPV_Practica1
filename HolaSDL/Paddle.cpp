#include "Paddle.h"
#include <iostream>
#include "checkML.h"

Paddle::Paddle() : MovingObject() {}

Paddle::Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t) :
	MovingObject(pos, w, h, t, speed){}


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