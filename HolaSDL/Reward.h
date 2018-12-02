#pragma once

#include <iostream>
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "MovingObject.h"
#include "Paddle.h"
#include <list>

class Game;
class Reward: public MovingObject {
private:
	uint type;
	uint index;
	Paddle* paddle;
	Game* game;

	int animVel = 0;
	int animFrame = 0;
	int ticks = 0;

	bool used = false;

	list<ArkanoidObject*>::iterator itList;
public:
	Reward(Vector2D pos, uint w, uint h, uint tipo, Vector2D vel, Paddle* p, Texture* t, Game* g, list<ArkanoidObject*>::iterator list, uint ind);
	virtual void action() = 0;
	void update();
	void render();
	void handleEvents();
	void kindHelp();
	void deleteReward();
	bool collides();
	uint getTimeElapsed();
};