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
	lifes = 3;
	ballpos = Vector2D (400, 400);
	ballspeed = Vector2D(0.02, -0.02);
	ball = new Ball(ballpos, 15, 15, ballspeed, textures[0], this);
	Vector2D paddlepos(400, 500);
	Vector2D paddlespeed(20, 0);
	paddle = new Paddle(paddlepos, 100, 20, paddlespeed, textures[2]);
	Vector2D rightwallpos(775, 0);
	rightwall = new Wall(20, WIN_HEIGHT, rightwallpos, textures[3]);
	Vector2D leftwallpos(5, 0);
	leftwall = new Wall(20, WIN_HEIGHT, leftwallpos, textures[3]);
	Vector2D topwallpos(0, 0);
	topwall = new Wall(WIN_WIDTH, 20, topwallpos, textures[4]);
	blocksmap = new BlocksMap(300, 300, textures[1]);
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

bool Game::collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector)
{
	if (SDL_HasIntersection(rect, rightwall->getDestRect())) {
		collVector=Vector2D(-1, 0);
		return true;
	}
	else if (SDL_HasIntersection(rect, leftwall->getDestRect())) {
		collVector = Vector2D(1, 0);
		return true;
	}
	else if (SDL_HasIntersection(rect, topwall->getDestRect())) {
		collVector = Vector2D(0, -1);
		return true;
	}
	else if (SDL_HasIntersection(rect, paddle->getDestRect())) {
		double ballWidth = rect->w;
		double ballCenterX = rect->x + ballWidth / 2;
		SDL_Rect* paddlerect = paddle->getDestRect();
		double paddleWidth = paddlerect->w;
		double paddleCenterX = paddlerect->x + paddleWidth / 2;
		/*double speedX = m_ball.speedX();
		double speedY = m_ball.speedY();
		double speedXY = Math.sqrt(speedX*speedX + speedY * speedY);
		double posX = (ballCenterX - paddleCenterX) / (paddleWidth / 2);
		final double influenceX = 0.75;
		speedX = speedXY * posX * influenceX;
		m_ball.setSpeedX(speedX);
		speedY = Math.sqrt(speedXY*speedXY - speedX * speedX) *
			(speedY > 0 ? -1 : 1);
		m_ball.setSpeedY(speedY);*/
		int middleX = paddlerect->x + (paddlerect->w / 2);
		if(rect->x < middleX)
			collVector = Vector2D(0.5, 1);
		else if(rect->x > middleX)
			collVector = Vector2D(0.5, 1);
		else
			collVector = Vector2D(0, 1);
		collVector.normalize();
		return true;
	}
	else if (SDL_HasIntersection(rect, blocksmap->getDestRect()))
	{
		Block* block = blocksmap->collides(rect, speed, collVector);
		if (block != nullptr)
			blocksmap->ballHitsBlock(block);
		if (blocksmap->blockNumber() == 0)
			win = true;
	}
}
void Game::death() {
	if (lifes > 1) {
		lifes--;
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	}
	else
	{
		lifes = 3;
		cout << "HAS PERDIDO";
	}
	cout << lifes << endl;
}

