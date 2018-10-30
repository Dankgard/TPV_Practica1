#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

typedef unsigned int uint;

class Ball {
private:
	Vector2D pos;
	uint w = 0;
	uint h = 0;
	Vector2D speed;
	SDL_Rect destRect;
	Texture* texture = nullptr;

public:
	Ball();
	Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t);
	~Ball() {}	
	void render();
	void update();
};
