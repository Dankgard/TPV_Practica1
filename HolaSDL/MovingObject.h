#pragma once

#include "ArkanoidObject.h"
#include <iostream>
#include "checkML.h"
#include "Vector2D.h"

class MovingObject : public ArkanoidObject {
protected:
	Vector2D speed;

public:
	MovingObject();
	MovingObject(Vector2D pos, uint w, uint h, Texture* t, Vector2D spe);

	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file);
	Vector2D getSpeed();
	void setSpeed(Vector2D newSpeed);
};