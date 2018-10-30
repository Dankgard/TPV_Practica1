#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"


typedef unsigned int uint;
class Game;
class Ball {
private:
	Vector2D pos;
	uint w = 0;
	uint h = 0;
	Vector2D speed;
	Texture* texture = nullptr;
	Game* game = nullptr;

public:
	Ball();
	Ball(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t, Game* g);
	~Ball() {}	
	void render() const;
	void update();
	SDL_Rect getDestRect();
};
