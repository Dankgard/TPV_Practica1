#include "BlocksMap.h"
#include <iostream>
#include "checkML.h"

BlocksMap::BlocksMap(uint mapW, uint mapH, uint cellW, uint cellH)
{
	uint colNumber = mapW / cellW;
	uint rowNumber = mapH / cellH;

	blocks = new Block[rowNumber, colNumber];
}