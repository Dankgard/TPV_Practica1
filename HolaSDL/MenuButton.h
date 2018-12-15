#pragma once

#include "GameObject.h"
#include "Texture.h"

class MenuButton : public GameObject {
private:
	int x, y, w, h;
	Texture* texture;
public:
	MenuButton(Texture* t, int x, int y, int w, int h);
	~MenuButton();

	void render();
	void handleEvents(SDL_Event e);
};
