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
	int tipoType;
	Paddle* paddle;
	Game* game;

	int animationVel = 0;
	int Frame = 0;

	list<ArkanoidObject>::iterator itList;
public:
	Reward();
	Reward(Vector2D Pos, int w, int h, int tipo, Vector2D vel, Paddle* p, Texture* t, Game* g, list<ArkanoidObject*>::iterator list);
	virtual void action() = 0;
	void update();
	void render();
	void handleEvents();
	void KindHelp();
};