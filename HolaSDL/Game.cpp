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
		textures[i] = new Texture(renderer);
		textures[i]->load("..//images//" + nombre[i],1,1);
	}

	// We finally create the game objects
	Vector2D ballpos (400, 400);
	Vector2D ballspeed(0.2,-0.2);
	ball = new Ball(ballpos, 25, 25, ballspeed, textures[0]);
	Vector2D paddlepos(400, 500);
	Vector2D paddlespeed(0, 0);
	paddle = new Paddle(paddlepos, 100, 20, paddlespeed, textures[2]);
	Vector2D rightwallpos(775, 0);
	rightwall = new Wall(20, WIN_HEIGHT, rightwallpos, textures[3]);
	Vector2D leftwallpos(5, 0);
	leftwall = new Wall(20, WIN_HEIGHT, leftwallpos, textures[3]);
	Vector2D topwallpos(0, 0);
	topwall = new Wall(WIN_WIDTH, 20, topwallpos, textures[4]);
	blocksmap = new BlocksMap(0,0,50,30);
	blocksmap->loadMap("..//maps//level01.ark", textures[1]);
	
}
Game::~Game() {
	delete ball;
	delete blocksmap;
	delete rightwall;
	delete leftwall;
	delete topwall;
	delete paddle;
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
	ball->update();
}

void Game::render() const {
	SDL_RenderClear(renderer);
	paddle->render();
	ball->render();
	rightwall->render();
	leftwall->render();
	topwall->render();
	blocksmap->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event) && !exit) {
		if(event.type == SDL_QUIT) exit = true;
		paddle->handleEvents(event);
	}
}

