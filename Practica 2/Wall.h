#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Wall: public ArkanoidObject {
private:
	string posWall;

public:
	Wall();
	Wall(string position,uint w, uint h, Vector2D pos, Texture* t);
	~Wall() {}

	virtual void update();
	virtual void handleEvents(SDL_Event event);

	bool collides(const SDL_Rect* rect, Vector2D& collVector);
};