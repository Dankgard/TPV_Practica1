#include "BlocksMap.h"
#include "Texture.h"
#include <iostream>
#include "Game.h"
#include "checkML.h"
#include <fstream>
#include <string>
#include <time.h>

BlocksMap::BlocksMap() : blocks(), ArkanoidObject() {}
BlocksMap::BlocksMap(uint w, uint h, Texture* t)
	: blocks(), ArkanoidObject(Vector2D(0, 0), w, h, t) {}

void BlocksMap::update()
{

}

void BlocksMap::handleEvents(SDL_Event event)
{

}

BlocksMap::~BlocksMap() {
	if (blocks != nullptr) {
		for (int a = 0; a < columns; a++) {
			for (int b = 0; b < rows; b++) {
				delete blocks[a][b];
			}
			delete blocks[a];
		}
		delete[] blocks;
		blocks = nullptr;
	}
}

// carga el mapa de un fichero de texto
void BlocksMap::loadMap(string filename, Texture* texture)
{
		ifstream input;
		input.open(filename);

		if (!input.is_open()) throw "No se encuentra el fichero";
		else
		{
			input >> rows;
			input >> columns;
			blocks = new Block**[columns];
			for (uint x = 0; x < columns; x++) {
				blocks[x] = new Block*[rows];
			}

			for (uint i = 0;i < rows;i++)
			{
				for (uint j = 0;j < columns;j++)
				{
					int margen = (WIN_WIDTH - w) / 2;
					int posX = j * (w / columns) + margen;
					int posY = i * (h / rows) + 20;
					uint color;
					input >> color;
					blocks[j][i] = new Block(w / columns, h / rows, color, i, j, Vector2D(posX,posY), texture);
				}
				uint x = blocks[0][0]->getX();
				uint y = blocks[0][0]->getY();
				pos = Vector2D(x, y);
			}
		}
		input.close();
}

// renderiza el mapa de bloques
void BlocksMap::render() const
{
	for (uint i = 0;i < rows;i++)
	{
		for (uint j = 0; j < columns;j++)
		{
			blocks[j][i]->render();
		}
	}
}

// devuelve el numero de bloques no destruidos
uint BlocksMap::blockNumber() const
{
	uint blockNumber = 0;	
	for (uint i = 0;i < rows;i++)
	{
		for (uint j = 0; j < columns;j++)
		{
			if (blocks[j][i]->getColor() != 0)
				blockNumber++;
		}
	}	
	return blockNumber;
}


/*  Devuelve el puntero al bloque del mapa de bloques al que pertenece el punto p.
	En caso de no haber bloque en ese punto (incluido el caso de que p esté fuera
	del espacio del mapa) devuelve nullptr.
*/
Block* BlocksMap::blockAt(const Vector2D& p) {
	
	bool encontrado = false;
	for (int y=0;y<rows;y++)
	{
		for (int x=0;x<columns;x++)
		{
			if(blocks[x][y] !=nullptr)
			if (p.getX() >= blocks[x][y]->getX() && p.getY() >= blocks[x][y]->getY() && p.getX() <= (blocks[x][y]->getX() + blocks[x][y]->getW()) && p.getY() <= (blocks[x][y]->getY() + blocks[x][y]->getH()))
				return blocks[x][y];		
		}							
	}
	return nullptr;		
}

// destruye el bloque block
void BlocksMap::ballHitsBlock(Block* block)
{
	block->setColor(0);
	
}

bool BlocksMap::collision(const SDL_Rect* rect, const Vector2D* ballVel, Vector2D& collVector, Game* game)
{
	bool collide = false;
	if (SDL_HasIntersection(rect, &getDestRect()))
	{
		Block* block = collides(rect, ballVel, collVector);
		if (block != nullptr)
		{
			ballHitsBlock(block);
			srand(time(NULL));
			if (rand() % 7 == 0) {
				game->spawnReward(Vector2D(block->getX(), block->getY()));
			}
		}
		if (blockNumber() == 0)
			game->nextLevel();
		collide = true;
	}
	return collide;
}

/* Dados el rectángulo y vector de dirección de la pelota, devuelve un puntero al
   bloque con el que ésta colisiona (nullptr si no colisiona con nadie) y el
   vector normal perpendicular a la superficie de colisión.
*/
Block* BlocksMap::collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector) {
	Vector2D p0 = { (double)ballRect->x, (double)ballRect->y }; // top-left
	Vector2D p1 = { (double)ballRect->x + (double)ballRect->w, (double)ballRect->y }; // top-right
	Vector2D p2 = { (double)ballRect->x, (double)ballRect->y + (double)ballRect->h }; // bottom-left
	Vector2D p3 = { (double)ballRect->x + (double)ballRect->w, (double)ballRect->y + (double)ballRect->h }; // bottom-right
	Block* b = nullptr;
	if (ballVel->getX() < 0 && ballVel->getY() < 0) {
		if ((b = blockAt(p0)) && b->getColor() != 0) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1)) && b->getColor() != 0) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2)) && b->getColor() != 0) collVector = { 1,0 };
	}
	else if (ballVel->getX() >= 0 && ballVel->getY() < 0) {
		if ((b = blockAt(p1)) && b->getColor() != 0) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel->getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0)) && b->getColor() != 0) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3)) && b->getColor() != 0) collVector = { -1,0 };
	}
	else if (ballVel->getX() > 0 && ballVel->getY() > 0) {
		if ((b = blockAt(p3)) && b->getColor() != 0) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2)) && b->getColor() != 0) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1)) && b->getColor() != 0) collVector = { -1,0 };
	}
	else if (ballVel->getX() < 0 && ballVel->getY() > 0) {
		if ((b = blockAt(p2)) && b->getColor() != 0) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3)) && b->getColor() != 0) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0)) && b->getColor() != 0) collVector = { 1,0 };
	}
	return b;
}
