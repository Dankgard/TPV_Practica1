#include "Wall.h"
#include <iostream>
#include "checkML.h"

Wall::Wall() : ArkanoidObject() {}

Wall::Wall(uint w, uint h, Vector2D pos, Texture* t) :
	ArkanoidObject(pos,w,h,t) {}
