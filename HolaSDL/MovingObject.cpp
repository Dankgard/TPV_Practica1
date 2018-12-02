#include "MovingObject.h"
#include <iostream>
#include "checkML.h"
#include <fstream>

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

void MovingObject::loadFromFile(ifstream& file)
{
	double speedX;
	double speedY;
	file >> speedX;
	file >> speedY;
	speed = Vector2D(speedX, speedY);
	ArkanoidObject::loadFromFile(file);
}

void MovingObject::saveToFile(ofstream& file)
{
	file << speed.getX() << " ";
	file << speed.getY() << " ";
	ArkanoidObject::saveToFile(file);
}