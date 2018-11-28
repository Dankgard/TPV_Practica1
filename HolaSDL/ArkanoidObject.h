#pragma once

#include <iostream>
#include "checkML.h"
#include "Texture.h"
#include "Vector2D.h"
#include "GameObject.h"

class ArkanoidObject: public GameObject {
protected:
	Vector2D pos;
	uint w = 0;
	uint h = 0;
	Texture* texture = nullptr;

	
public:
	ArkanoidObject();
	ArkanoidObject(Vector2D pos, uint w, uint h, Texture* t);

	void render();
	void renderFrame(int fila, int col);
	void loadFromFile();
	void saveToFile() const;

	SDL_Rect getDestRect();
	uint getX() { return pos.getX(); }
	uint getY() { return pos.getY(); }
	uint getW() { return w; }
	uint getH() { return h; }

};