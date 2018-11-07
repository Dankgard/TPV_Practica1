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

	// We now create the textures
	for(uint i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer);
		try {
			textures[i]->load("..//images//" + nombre[i], 1, 1);
		}
		catch (string s)
		{
			throw s;
		}
	}

	// We finally create the game objects
	lifes = 3;
	ballpos = Vector2D (400, 400);
	ballspeed = Vector2D(0.02, -0.02);
	ball = new Ball(ballpos, 15, 15, ballspeed, textures[(int)balltexture], this);
	Vector2D paddlepos(400, 500);
	Vector2D paddlespeed(20, 0);
	paddle = new Paddle(paddlepos, 100, 20, paddlespeed, textures[(int)paddletexture]);
	Vector2D rightwallpos(775, 0);
	rightwall = new Wall(20, WIN_HEIGHT, rightwallpos, textures[(int)sidetexture]);
	Vector2D leftwallpos(5, 0);
	leftwall = new Wall(20, WIN_HEIGHT, leftwallpos, textures[(int)sidetexture]);
	Vector2D topwallpos(0, 0);
	topwall = new Wall(WIN_WIDTH, 20, topwallpos, textures[(int)topsidetexture]);
	blocksmap = new BlocksMap(600, 300, textures[1]);
	try {
		blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);
	}
	catch (string s)
	{
		throw s;
	}
	cout << "Lifes: " << lifes << endl;
	
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

// bucle principal
void Game::run() {
	while(!exit) {
		// Falta el control de tiempo
		handleEvents();
		update();
		render();
	}
}

// actualiza el estado del juego
void Game::update() {
	ball->update();

	if (win)
	{
		if (currentLevel == 2)
		{
			cout << "YOU WON THE GAME";
			exit = true;
		}
		else
		{
			win = false;
			currentLevel++;
			cout << "Next Level" << endl;
			try {
				blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);
			}
			catch (string s)
			{
				throw s;
			}
		}
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
		SDL_Delay(3000);
	}

	if (exit)
	{
		SDL_Quit();
	}
}

// renderiza todos los objetos
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

// maneja los eventos de teclado
void Game::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event) && !exit) {
		if(event.type == SDL_QUIT) exit = true;
		paddle->handleEvents(event);
	}
}

// detecta si la bola colisiona y actualiza su vector de colision
bool Game::collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector)
{
	bool collides = false;

	if (SDL_HasIntersection(rect, rightwall->getDestRect())) {
		collVector=Vector2D(-1, 0);
		collides = true;
	}
	else if (SDL_HasIntersection(rect, leftwall->getDestRect())) {
		collVector = Vector2D(1, 0);
		collides = true;
	}
	else if (SDL_HasIntersection(rect, topwall->getDestRect())) {
		collVector = Vector2D(0, -1);
		collides = true;
	}
	else if (SDL_HasIntersection(rect, paddle->getDestRect())) {
		SDL_Rect* paddlerect = paddle->getDestRect();
		int middleX = paddlerect->x + (paddlerect->w / 2);
		if(rect->x < middleX)
			collVector = Vector2D(0.15, 1);
		else if(rect->x > middleX)
			collVector = Vector2D(-0.15, 1);
		else
			collVector = Vector2D(0, 1);
		collides = true;
	}
	else if (SDL_HasIntersection(rect, blocksmap->getDestRect()))
	{
		Block* block = blocksmap->collides(rect, speed, collVector);
		if (block != nullptr)
			blocksmap->ballHitsBlock(block);
		if (blocksmap->blockNumber() == 0)
			win = true;
		collides = true;
	}
	collVector.normalize();
	return collides;
}

// maneja como actuar cuando el jugador pierde una vida
void Game::death() {
	if (lifes > 1) {
		lifes--;
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	}
	else
	{
		cout << "GAME OVER";
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
		SDL_Delay(3000);
		currentLevel = 0;
		try {
			blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);
		}
		catch (string s)
		{
			throw s;
		}
		lifes = 3;
	}
	cout << "Lifes: " << lifes << endl;
}

