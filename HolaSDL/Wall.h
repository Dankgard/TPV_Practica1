#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Wall: public ArkanoidObject {
private:
	string PosWall;

public:
	Wall();
	Wall(string Position,uint w, uint h, Vector2D pos, Texture* t);
	~Wall() {}

	bool collides(const SDL_Rect* rect, Vector2D& collVector);
};