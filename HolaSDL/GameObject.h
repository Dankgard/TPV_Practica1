#pragma once

#include <iostream>
#include "checkML.h"

class GameObject {
private:


public:
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvents(SDL_Event event) = 0;
};