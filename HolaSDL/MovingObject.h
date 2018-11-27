#pragma once

#include "ArkanoidObject.h"
#include <iostream>
#include "checkML.h"

class MovingObject: public ArkanoidObject {
protected:
	Vector2D speed;

public:
	MovingObject();
	MovingObject(Vector2D pos, uint w, uint h, Texture* t, Vector2D speed);
	void loadFromFile();
	void saveToFile();
	Vector2D getSpeed();
	void setSpeed(Vector2D newSpeed);
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvents(SDL_Event event) = 0;
};
