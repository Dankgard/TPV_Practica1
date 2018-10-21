#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

typedef unsigned int uint;

class Paddle {
private:
	Vector2D pos;
	uint w = 0;
	uint h = 0;
	Vector2D speed;
	Texture* texture = nullptr;

public:
	Paddle();
	Paddle(Vector2D pos, uint w, uint h, Vector2D speed, Texture* t);
	~Paddle() {}
	void render() const;
};