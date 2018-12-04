#include <iostream>
#include "ArkanoidObject.h"
#include "Game.h"
#include "checkML.h"
#include <fstream>

using namespace std;

ArkanoidObject::ArkanoidObject() :
	pos(), w(), h(), texture() {}

ArkanoidObject::ArkanoidObject(Vector2D pos, uint w, uint h, Texture* t) :
	pos(pos), w(w), h(h), texture(t) {}

void ArkanoidObject::render()
{
	SDL_Rect destRect = getDestRect();
	texture->render(destRect, SDL_FLIP_NONE);
}

void ArkanoidObject::renderFrame(int row, int col) {
	SDL_Rect dstRect = getDestRect();
	
	texture->renderFrame(dstRect, row, col, 0, SDL_FLIP_NONE);
}

SDL_Rect ArkanoidObject::getDestRect()
{
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.h = h;
	destRect.w = w;
	return destRect;
}

void ArkanoidObject::loadFromFile(ifstream& file)
{
	double x;
	double y;
	file >> x >> y >> w >> h;
	//file >> y;
	pos = Vector2D(x, y);
	//file >> w;
	//file >> h;
}

void ArkanoidObject::saveToFile(ofstream& file)
{
	file << (uint)pos.getX() << " ";
	file << (uint)pos.getY() << " ";
	file << w << " ";
	file << h << endl;
}

