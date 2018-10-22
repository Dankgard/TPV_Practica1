#include "BlocksMap.h"
#include <iostream>
#include "checkML.h"
#include <fstream>
#include <string>

BlocksMap::BlocksMap() : blocks(), mapH(), mapW(), cellH(), cellW() {}
BlocksMap::~BlocksMap() {
	uint colNumber = sizeof blocks[0] / sizeof blocks[0, 0];

	for (uint a = 0; a < colNumber; a++) {
		delete[] blocks[a];
	}
	delete[] blocks;
}

void BlocksMap::loadMap(string filename)
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
		blocks = new Block*[colNumber];
		for (uint x = 0; x < colNumber; x++) {
			blocks[x] = new Block[rowNumber];
		}

		for (uint i = 0;i < rowNumber;i++)
		{
			for (uint j = 0;j < colNumber;j++)
			{
				uint c;
				input >> c;
				blocks[j][i].setColor(c);
			}
		}
	}
	input.close();
}

void BlocksMap::render() const
{
	uint rowNumber = sizeof blocks / sizeof blocks[0];
	uint colNumber = sizeof blocks[0] / sizeof blocks[0,0];
	for (uint i = 0;i < rowNumber;i++)
	{
		for (uint j = 0; j < colNumber;j++)
		{
			blocks[j][i].render();
		}
	}
}

uint BlocksMap::blockNumber() const
{
	uint blockNumber = 0;
	uint rowNumber = sizeof blocks / sizeof blocks[0];
	uint colNumber = sizeof blocks[0] / sizeof blocks[0, 0];
	for (uint i = 0;i < rowNumber;i++)
	{
		for (uint j = 0; j < colNumber;j++)
		{
			if (blocks[j][i].getColor() != 0)
				blockNumber++;
		}
	}
	return blockNumber;
}