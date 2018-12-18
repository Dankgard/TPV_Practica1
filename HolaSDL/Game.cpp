#include "Game.h"
#include <iostream>
#include "checkML.h"
#include "Texture.h"
#include <time.h> 

using namespace std;

Game::Game() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	// We now create the textures
	for (uint i = 0; i < NUM_TEXTURES - 2; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load("..//images//" + nombre[i], 1, 1);
	}
	textures[brickstexture] = new Texture(renderer, "..//images//" + nombre[brickstexture], 2, 3);
	textures[rewardtexture] = new Texture(renderer, "..//images//" + nombre[rewardtexture], 10, 8);

	currentLevel = 0;
	lifes = 3;
	cout << "Lifes: " << lifes << endl;

	blocksmap = new BlocksMap(600, 300, textures[brickstexture]);
	blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[brickstexture]);
	paddle = new Paddle(Vector2D(400, 500), 100, 20, Vector2D(20, 0), textures[paddletexture]);
	ballpos = Vector2D(400, 400);
	ballspeed = Vector2D(2, -2);
	ball = new Ball(ballpos, 15, 15, ballspeed, textures[balltexture], this);
	leftwall = new Wall("left", 20, WIN_HEIGHT, Vector2D(5, 0), textures[sidetexture]);
	rightwall = new Wall("right", 20, WIN_HEIGHT, Vector2D(775, 0), textures[sidetexture]);	
	topwall = new Wall("top", WIN_WIDTH, 20, Vector2D(0, 0), textures[topsidetexture]);	

	loadList();
}


Game::Game(string filename) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init (SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH, WIN_HEIGHT,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	if(window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	// We now create the textures
	for(uint i = 0; i < NUM_TEXTURES-2; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load("..//images//" + nombre[i], 1, 1);	
	}
	textures[brickstexture] = new Texture(renderer, "..//images//" + nombre[brickstexture], 2, 3);
	textures[rewardtexture] = new Texture(renderer, "..//images//" + nombre[rewardtexture], 10, 8);

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
		cout << "Lifes: " << lifes << endl;
		blocksmap = new BlocksMap(0, 0, textures[brickstexture]);
		blocksmap->loadFromFile(file, textures[brickstexture]);
		//blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[brickstexture]);
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
	for (auto arkanoidObject : arkanoidObjects)
		delete arkanoidObject;	
	/*delete paddle;
	delete ball;
	delete blocksmap;
	delete leftwall;
	delete rightwall;
	delete topwall;*/
	for(uint i = 0; i < NUM_TEXTURES; i++)
		delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// bucle principal
void Game::run() {
	while(!exit) {		
		handleEvents();
		update();
		render();
	}
}

// actualiza el estado del juego
void Game::update() {	

	//PLAY
	for (list<ArkanoidObject*>::iterator it = arkanoidObjects.begin(); it != arkanoidObjects.end();) {
		((*it++))->update();
	}	
	int startTime = SDL_GetTicks();
	int frameTime = SDL_GetTicks() - startTime;
	if (frameTime < FRAME_RATE) {
		SDL_Delay(FRAME_RATE - frameTime);
	}
}

// renderiza todos los objetos
void Game::render(){

	SDL_RenderClear(renderer);
	for (auto arkanoidObject : arkanoidObjects)
	{	
		
		arkanoidObject->render();
		
	}	
	SDL_RenderPresent(renderer);
}

// maneja los eventos de teclado
void Game::handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
		{		
			exit = true;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_s:
				saveGame();
				break;

			case SDLK_ESCAPE:
				exit = true;
				break;
			}
			
		}
		paddle->handleEvent(event);
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
	ballpos = Vector2D(400, 400);
	if (ballspeed.getY() > 0) {
		ballspeed = Vector2D(ballspeed.getX(), -ballspeed.getY());
	}
	if (lifes > 1) {
		lifes--;
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	}
	else
	{
		cout << "GAME OVER" << endl;
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
		SDL_Delay(3000);
		currentLevel = 0;
		uint blocksmapW = blocksmap->getW();
		uint blocksmapH = blocksmap->getH();
		arkanoidObjects.remove(blocksmap);
		delete blocksmap;
		blocksmap = new BlocksMap(blocksmapW, blocksmapH, textures[brickstexture]);
		blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);
		arkanoidObjects.push_front(blocksmap);
		lifes = 3;
	}
	cout << "Lifes: " << lifes << endl;
}

// avanza al siguiente nivel
void Game::nextLevel()
{
	ballpos = Vector2D(400, 400);
	if (ballspeed.getY() > 0) {
		ballspeed = Vector2D(ballspeed.getX(), -ballspeed.getY());
	}

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
		uint blocksmapW = blocksmap->getW();
		uint blocksmapH = blocksmap->getH();
		arkanoidObjects.remove(blocksmap);
		delete blocksmap;
		blocksmap = new BlocksMap(blocksmapW, blocksmapH, textures[brickstexture]);
		blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[(int)brickstexture]);		
		arkanoidObjects.push_front(blocksmap);
	}
	ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	SDL_Delay(500);
}

void Game::extraLife()
{
	lifes++;
	cout << "Lifes: " << lifes << endl;
}

void Game::killObject(Reward* r)
{
	for (list<ArkanoidObject*>::iterator list = arkanoidObjects.begin(); list != arkanoidObjects.end(); ++list) {
		if ((*list) == r) {
			delete r;
			arkanoidObjects.erase(list);
			break;
		}
	}
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
	cout << "Escribe el nombre de la partida: " << endl;
	string partida;
	cin >> partida;
	string filename = "..\\saves\\" + partida + ".txt";

	ofstream file(filename, ofstream::trunc);

	file << currentLevel << endl;
	file << lifes << endl;

	for (auto arkanoidObject : arkanoidObjects) {
		arkanoidObject->saveToFile(file);
	}		

	file.close();
	exit = true;	
}

void Game::spawnReward(Vector2D pos)
{
	srand(time(NULL));
	uint type = rand() % 4;
	list<ArkanoidObject*>::iterator it = arkanoidObjects.end();
	Reward* powerUp = new Reward(pos, 50, 20, powerUpType[type], Vector2D(0, 2), paddle, textures[rewardtexture], this, it);
	arkanoidObjects.push_back(powerUp);
}


