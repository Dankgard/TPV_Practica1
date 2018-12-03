#include "Menu.h"
#include "Game.h"
#include "Texture.h"
#include "checkML.h"

Menu::Menu() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		MENU_WIDTH, MENU_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
}