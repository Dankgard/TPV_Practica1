#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"

typedef unsigned int uint;
class Game;
class Ball: public MovingObject {
private:
	Game* game = nullptr;

public:
	Ball();
	Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t, Game* g);
	~Ball() {}	
	void update();
	void resetBall(Vector2D originalPos, double speedX, double speedY);
};
