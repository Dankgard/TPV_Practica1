#include "Game.h"
#include <iostream>
#include "checkML.h"
#include "Texture.h"

using namespace std;

Game::Game() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init (SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH, WIN_HEIGHT,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	if(window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	string nombre[NUM_TEXTURES] = { "ball.png","bricks.png","paddle.png","side.png","topside.png" };
	// We now create the textures
	for(uint i = 0; i < NUM_TEXTURES; i++) {
		textures[i]->load("..//images//" + nombre[i],1,1);
	}

	// We finally create the game objects
	Vector2D ballpos = new Vector2D(400, 500);
	ball = new Ball(ballpos);
	//helicopter = new Helicopter(...);
	
}
Game::~Game() {
	for(uint i = 0; i < NUM_TEXTURES; i++)
		delete textures[i];
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
}

void Game::run() {
	while(!exit) {
		// Falta el control de tiempo
		handleEvents();
		update();
		render();
	}
}

void Game::update() {
	//dog->update();
}

void Game::render() const {
	SDL_RenderClear(renderer);
	//dog->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event) && !exit) {
		if(event.type == SDL_QUIT) exit = true;
		//dog->handleEvents(event);
	}
}

