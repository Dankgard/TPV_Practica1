#include "Wall.h"
#include <iostream>
#include "checkML.h"

Wall::Wall() : ArkanoidObject() {}

Wall::Wall(string Position, uint w, uint h, Vector2D pos, Texture* t) :
	ArkanoidObject(pos, w, h, t) {
	PosWall = Position;
}

bool Wall::collides(const SDL_Rect* rect, Vector2D& collVector) {
	if (SDL_HasIntersection(rect, &getDestRect())) {
		if (PosWall == "left")
			collVector = Vector2D(1, 0);
		if (PosWall == "right")
			collVector = Vector2D(-1, 0);
		if (PosWall == "top")
			collVector = Vector2D(0, -1);
		return true;
	}
	else
		return false;
}
