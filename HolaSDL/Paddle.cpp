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
void Paddle::mov(int speed){
	if (pos.getX() >= 20-speed && pos.getX()<=780-w-speed)
		pos = Vector2D(pos.getX() + speed, pos.getY());
}

SDL_Rect* Paddle::getDestRect() {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	return &destRect;
}

void Paddle::handleEvents(SDL_Event event) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:			
			mov(-10);
			break;
		case SDLK_RIGHT:			
			mov(10);			
			break;
		default:
			break;
		}
	}
}