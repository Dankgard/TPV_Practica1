#pragma once

#include <iostream>
#include "Block.h"
#include "checkML.h"

typedef unsigned int uint;

class BlocksMap {
private:
	Block** blocks = nullptr;
	uint mapW = 0;
	uint mapH = 0;
	uint cellW = 0;
	uint cellH = 0;
	

public:
	BlocksMap();
	~BlocksMap();
	void loadMap(string filename);
	void render() const;
	uint blockNumber() const;
};
