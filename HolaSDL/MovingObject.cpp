#include "MovingObject.h"
#include <iostream>
#include "checkML.h"

MovingObject::MovingObject() :
	ArkanoidObject(), speed() {}

MovingObject::MovingObject(Vector2D pos, uint w, uint h, Texture* t, Vector2D spe) :
	ArkanoidObject(pos, w, h, t) {
	speed = spe;
}

Vector2D MovingObject::getSpeed()
{
	return speed;
}

void MovingObject::setSpeed(Vector2D newSpeed)
{
	speed = newSpeed;
}