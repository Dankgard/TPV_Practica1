#include "Game.h"
#include <iostream>
#include "checkML.h"
#include "Texture.h"
#include <time.h> 

using namespace std;

Game::Game(string filename) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init (SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH, WIN_HEIGHT,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	if(window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	// We now create the textures
	for(uint i = 0; i < NUM_TEXTURES-1; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load("..//images//" + nombre[i], 1, 1);	
	}
	textures[rewardtexture] = new Texture(renderer);
	textures[rewardtexture]->load("..//images//" + nombre[rewardtexture], 10, 8);

	// We finally create the game objects
	ifstream file;
	if (file.fail()) {
		throw "Error loading " + filename;
	}
	else
	{
		saveFile = "..//saves//" + filename + ".txt";
		file.open(saveFile);
		file >> currentLevel;
		file >> lifes;
		blocksmap = new BlocksMap(0, 0, textures[brickstexture]);
		blocksmap->loadFromFile(file);
		blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);
		paddle = new Paddle(Vector2D(0, 0), 0, 0, Vector2D(0, 0), textures[paddletexture]);
		paddle->loadFromFile(file);
		ball = new Ball(Vector2D(0, 0), 0, 0, Vector2D(0, 0), textures[balltexture], this);
		ball->loadFromFile(file);
		ballpos = ball->getPos();
		ballspeed = ball->getSpeed();
		leftwall = new Wall("left", 0, 0, Vector2D(0, 0), textures[sidetexture]);
		leftwall->loadFromFile(file);
		rightwall = new Wall("right", 0, 0, Vector2D(0, 0), textures[sidetexture]);
		rightwall->loadFromFile(file);
		topwall = new Wall("top", 0, 0, Vector2D(0, 0), textures[topsidetexture]);
		topwall->loadFromFile(file);
		loadList();
		file.close();
	}	
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
		if (event.type == SDL_QUIT)
		{
			if(!savedGame)
				saveGame();
			exit = true;
		}
		paddle->handleEvents(event);
	}
}

// detecta si la bola colisiona y actualiza su vector de colision
bool Game::collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector)
{
	bool collides = false;

	if (rightwall->collides(rect, collVector))
		collides = true;
	else if (leftwall->collides(rect, collVector))
		collides = true;
	else if (topwall->collides(rect, collVector))
		collides = true;
	else if (paddle->collides(rect, collVector))
		collides = true;	
	else if (blocksmap->collision(rect,speed,collVector,this))
		collides = true;
	
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
		delete blocksmap;
		blocksmap = new BlocksMap(600, 300, textures[(int)brickstexture]);
		blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);	
		lifes = 3;
	}
	cout << "Lifes: " << lifes << endl;
}

// avanza al siguiente nivel
void Game::nextLevel()
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
		delete blocksmap;
		blocksmap = new BlocksMap(600, 300, textures[(int)brickstexture]);
		blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);
	}
	ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	SDL_Delay(3000);
}

void Game::extraLife()
{
	lifes++;
}

void Game::killObject(uint ind)
{

}

void Game::loadList()
{
	arkanoidObjects.push_back(blocksmap);
	arkanoidObjects.push_back(paddle);
	arkanoidObjects.push_back(ball);
	arkanoidObjects.push_back(leftwall);
	arkanoidObjects.push_back(rightwall);
	arkanoidObjects.push_back(topwall);
}

void Game::saveGame()
{
	ofstream file(saveFile, ofstream::trunc);
	file << currentLevel << endl;
	file << lifes << endl;
	for (auto arkanoidObject : arkanoidObjects)
		arkanoidObject->saveToFile(file);
	file.close();
	savedGame = true;
}

void Game::spawnReward(Vector2D pos)
{
	srand(time(NULL));
	uint type = rand() % 4;
	list<ArkanoidObject*>::iterator it = arkanoidObjects.end();
	Reward* powerUp = new Reward(pos, 50, 20, powerUpType[type], Vector2D(0, 2), paddle, textures[rewardtexture], this, it);
	arkanoidObjects.push_back(powerUp);
}


