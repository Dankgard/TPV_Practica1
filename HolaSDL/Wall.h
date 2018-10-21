#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

typedef unsigned int uint;

class Wall {
private:
	Vector2D pos;
	uint w = 0;
	uint h = 0;
	Texture* texture = nullptr;

public:
	Wall();
	Wall(uint w, uint h, Vector2D pos, Texture* t);
	~Wall() {}
	void render() const;
};