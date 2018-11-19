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
	ArkanoidObject(Vector2D pos, uint w, uint h, Texture* t);
	//virtual void render() const;
	void loadFromFile();
	void saveToFile() const;
	SDL_Rect getDestRect();

};