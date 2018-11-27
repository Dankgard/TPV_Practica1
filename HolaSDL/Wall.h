#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "ArkanoidObject.h"

typedef unsigned int uint;

class Wall: public ArkanoidObject {

public:
	Wall();
	Wall(uint w, uint h, Vector2D pos, Texture* t);
	~Wall() {}
};