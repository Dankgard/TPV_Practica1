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
	virtual ~ArkanoidObject() {}

	void render();
	void renderFrame(int fila, int col);
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);

	SDL_Rect getDestRect();
	uint getX() { return pos.getX(); }
	uint getY() { return pos.getY(); }
	uint getW() { return w; }
	uint getH() { return h; }
	Vector2D getPos() { return pos; }

};