#pragma once

#include <iostream>
#include "checkML.h"
#include "SDL.h" // Windows


class SdlApplication;
class GameObject {
public:	
	GameObject();
	~GameObject();

	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool handleEvents(SDL_Event& event) = 0;
};