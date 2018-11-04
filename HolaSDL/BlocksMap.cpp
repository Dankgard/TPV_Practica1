#include "BlocksMap.h"
#include "Texture.h"
#include <iostream>
#include "checkML.h"
#include <fstream>
#include <string>

BlocksMap::BlocksMap() : blocks(), mapH(), mapW(), cellH(), cellW() {}
BlocksMap::BlocksMap(uint mapW, uint mapH, uint cellW, uint cellH)
	: blocks(), mapW(mapW), mapH(mapH), cellW(cellW), cellH(cellH) {}

BlocksMap::~BlocksMap() {
	for (uint a = 0; a < mapW; a++) {
		delete[] blocks[a];
	}
	delete[] blocks;
}

void BlocksMap::loadMap(string filename, Texture* texture)
{
	ifstream input;
	input.open(filename);

	if (!input.is_open()) cout << "No se encuentra el fichero" << endl;
	else
	{
		uint rowNumber;
		uint colNumber;
		input >> rowNumber;
		input >> colNumber;
		mapW = colNumber;
		mapH = rowNumber;
		blocks = new Block**[colNumber];
		for (uint x = 0; x < colNumber; x++) {
			blocks[x] = new Block*[rowNumber];
		}
		//Para colocarlo en el medio de la imagen
		uint xold = (800 - (colNumber * cellW)) / 2;
		uint x = xold;
		uint y = 20;

		for (uint i = 0;i < rowNumber;i++)
		{
			for (uint j = 0;j < colNumber;j++)
			{				
				Vector2D pos(x + j*cellW, y + i*cellH);
				uint color;
				input >> color;
				blocks[j][i] = new Block(cellW, cellH, color, i, j, pos, texture);
				x++;
			}
			x = xold;
			y++;
		}
	}
	input.close();
}

void BlocksMap::render() const
{
	//uint rowNumber = mapH; //sizeof blocks / sizeof blocks[0];
	//uint colNumber = mapW; //sizeof blocks[0] / sizeof blocks[0, 0];
	for (uint i = 0;i < mapH;i++)
	{
		for (uint j = 0; j < mapW;j++)
		{
			blocks[j][i]->render();
		}
	}
}

uint BlocksMap::blockNumber() const
{
	uint blockNumber = 0;
	uint rowNumber = mapH;
	uint colNumber = mapW;
	for (uint i = 0;i < rowNumber;i++)
	{
		for (uint j = 0; j < colNumber;j++)
		{
			if (blocks[j][i]->getColor() != 0)
				blockNumber++;
		}
	}
	return blockNumber;
}

/* Dados el rectángulo y vector de dirección de la pelota, devuelve un puntero al
   bloque con el que ésta colisiona (nullptr si no colisiona con nadie) y el
   vector normal perpendicular a la superficie de colisión.
*/
Block* BlocksMap::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector) {
	Vector2D p0 = { (double)ballRect.x, (double)ballRect.y }; // top-left
	Vector2D p1 = { (double)ballRect.x + (double)ballRect.w, (double)ballRect.y }; // top-right
	Vector2D p2 = { (double)ballRect.x, (double)ballRect.y + (double)ballRect.h }; // bottom-left
	Vector2D p3 = { (double)ballRect.x + (double)ballRect.w, (double)ballRect.y + (double)ballRect.h }; // bottom-right
	Block* b = nullptr;
	if (ballVel.getX() < 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p0))) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2))) collVector = { 1,0 };
	}
	else if (ballVel.getX() >= 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p1))) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel.getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3))) collVector = { -1,0 };
	}
	else if (ballVel.getX() > 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p3))) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1))) collVector = { -1,0 };
	}
	else if (ballVel.getX() < 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p2))) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0))) collVector = { 1,0 };
	}
	return b;
}


/*  Devuelve el puntero al bloque del mapa de bloques al que pertenece el punto p.
	En caso de no haber bloque en ese punto (incluido el caso de que p esté fuera
	del espacio del mapa) devuelve nullptr.
*/
Block* BlocksMap::blockAt(const Vector2D& p) {
	
	// si se sale de los limites del mapa de bloques
	if (p.getX() < (blocks[0][0]->getX() - (cellW / 2)) || p.getX() > (blocks[mapW - 1][0]->getX() + (cellW / 2)) ||
		p.getY() < (blocks[0][0]->getY() - (cellH / 2)) || p.getY() > (blocks[0][mapH - 1]->getY() + (cellH / 2)))
		return nullptr;
	// si no, va buscando el bloque en el que se encuentra p
	else {
		int j;
		int i;
		while ((blocks[j][0]->getX() - (cellW / 2)) < p.getX())
		{
			j++;
		}
		while ((blocks[0][i]->getY() - (cellH / 2)) < p.getY())
		{
			i++;
		}
		return blocks[j-1][i-1];
	}
}