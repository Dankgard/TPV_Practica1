#include "Wall.h"
#include <iostream>
#include "checkML.h"

Wall::Wall() : ArkanoidObject() {}

Wall::Wall(string position, uint w, uint h, Vector2D pos, Texture* t) :
	ArkanoidObject(pos, w, h, t) {
	posWall = position;
}

void Wall::update()
{

}

bool Wall::handleEvents(SDL_Event& event)
{
	return true;
}

bool Wall::collides(const SDL_Rect* rect, Vector2D& collVector) {
	if (SDL_HasIntersection(rect, &getDestRect())) {
		if (posWall == "left")
			collVector = Vector2D(1, 0);
		if (posWall == "right")
			collVector = Vector2D(-1, 0);
		if (posWall == "top")
			collVector = Vector2D(0, -1);
		return true;
	}
	else
		return false;
}
