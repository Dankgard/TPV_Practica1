#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"

typedef unsigned int uint;

class Paddle: public MovingObject {
private:
	bool powered = false;
	uint originalTime = 5000;
	uint powerupTicks = 0;
	uint oldW = 100;
public:
	Paddle();
	Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t);
	~Paddle() {}

	bool collides(const SDL_Rect* rect, Vector2D& collVector);
	void mov(int speed);
	virtual void update();
	void handleEvents(SDL_Event event);
	void shorterPaddle();
	void longerPaddle();
	void originalPaddle();
	void Wsave();
	uint getTimeElapsed();
	void saveToFile(ofstream& file);
	void loadFromFile(ifstream& file);
};
