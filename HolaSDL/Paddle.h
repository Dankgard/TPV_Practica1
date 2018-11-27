#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"

typedef unsigned int uint;

class Paddle: public MovingObject {

public:
	Paddle();
	Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t);
	~Paddle() {}
	void mov(int speed);
	void handleEvents(SDL_Event event);
};