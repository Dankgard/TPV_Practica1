#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"

typedef unsigned int uint;
class PlayState;
class Ball: public MovingObject {
private:
	PlayState* game = nullptr;	

public:
	Ball();
	Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t, PlayState* g);
	~Ball() {}	

	void update();
	virtual bool handleEvents(SDL_Event& event);
	void resetBall(Vector2D originalPos, double speedX, double speedY);
};
