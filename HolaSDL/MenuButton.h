#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "SdlApplication.h"
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"

using CallBackOnClick = void(SdlApplication* app);

class MenuButton : public GameObject {
protected:
	int x, y, w, h;
	Texture* texture;
	SdlApplication* app;
	CallBackOnClick* cb;
public:
	MenuButton(Texture* t, int x, int y, int w, int h, void(*callback)(SdlApplication* app));
	~MenuButton();

	void render();	
	bool handleEvents(SDL_Event& e);
	void handleEvents(SDL_Event e) {};
	void update() {};
};
