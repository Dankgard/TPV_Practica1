#include "PlayState.h"
#include <time.h> 


PlayState::PlayState(SdlApplication* app): GameState(app)
{
	cout << app;

	currentLevel = 0;
	lifes = 3;
	cout << "Lifes: " << lifes << endl;

	blocksmap = new BlocksMap(600, 300, app->getTexture(brickst));
	blocksmap->loadMap("..//maps//" + levels[currentLevel], app->getTexture(brickst));
	paddle = new Paddle(Vector2D(400, 500), 100, 20, Vector2D(20, 0), app->getTexture(paddlet));
	ballpos = Vector2D(400, 400);
	ballspeed = Vector2D(2, -2);
	ball = new Ball(ballpos, 15, 15, ballspeed, app->getTexture(ballt), this);
	leftwall = new Wall("left", 20, SDL_WIN_HEIGHT, Vector2D(5, 0), app->getTexture(sidet));
	rightwall = new Wall("right", 20, SDL_WIN_HEIGHT, Vector2D(775, 0), app->getTexture(sidet));
	topwall = new Wall("top", SDL_WIN_WIDTH, 20, Vector2D(0, 0), app->getTexture(topsidet));

	loadList();
};

PlayState::PlayState(SdlApplication* app, string filename) : GameState(app)
{
	cout << app;

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
		blocksmap = new BlocksMap(0, 0, app->getTexture(brickst));
		blocksmap->loadFromFile(file, app->getTexture(brickst));
		//blocksmap->loadMap("..//maps//" + levels[currentLevel], textures[brickstexture]);
		paddle = new Paddle(Vector2D(0, 0), 0, 0, Vector2D(0, 0), app->getTexture(paddlet));
		paddle->loadFromFile(file);
		ball = new Ball(Vector2D(0, 0), 0, 0, Vector2D(0, 0), app->getTexture(ballt), this);
		ball->loadFromFile(file);
		ballpos = ball->getPos();
		ballspeed = ball->getSpeed();
		leftwall = new Wall("left", 0, 0, Vector2D(0, 0), app->getTexture(sidet));
		leftwall->loadFromFile(file);
		rightwall = new Wall("right", 0, 0, Vector2D(0, 0), app->getTexture(sidet));
		rightwall->loadFromFile(file);
		topwall = new Wall("top", 0, 0, Vector2D(0, 0), app->getTexture(topsidet));
		topwall->loadFromFile(file);
		loadList();
		file.close();
	}
};



PlayState::~PlayState()
{
	for (auto arkanoidObject : arkanoidObjects)
		delete arkanoidObject;
	/*delete paddle;
	delete ball;
	delete blocksmap;
	delete leftwall;
	delete rightwall;
	delete topwall;*/
}


void PlayState::renderExample()
{
	SDL_Rect dstRect;
	dstRect.x = 100;
	dstRect.y = 100;
	dstRect.w = 300;
	dstRect.h = 300;
	Texture* texture = app->getTexture(rewardt);
	texture->render(dstRect, SDL_FLIP_NONE);
}

bool PlayState::handleEvents(SDL_Event& event)
{	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			app->getStateMachine()->pushState(new PauseState(app));
			break;
		case SDLK_s:
			saveGame();
			break;
		}
		paddle->handleEvent(event);
	}
	else
	{
		GameState::handleEvents(event);
	}
	return true;
}

// bucle principal
void PlayState::run() {
	while (!exit) {
		handleEvents();
		update();
		render();
	}
}

// actualiza el estado del juego
void PlayState::update() {

	//PLAY
	for (list<ArkanoidObject*>::iterator it = arkanoidObjects.begin(); it != arkanoidObjects.end();) {
		((*it++))->update();
	}
	int startTime = SDL_GetTicks();
	int frameTime = SDL_GetTicks() - startTime;
	if (frameTime < SDL_FRAME_RATE) {
		SDL_Delay(SDL_FRAME_RATE - frameTime);
	}
}

// renderiza todos los objetos
void PlayState::render() {

	for (auto arkanoidObject : arkanoidObjects)
	{
		arkanoidObject->render();
	}
}

// maneja los eventos de teclado
void PlayState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
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
bool PlayState::collides(const SDL_Rect* rect, const Vector2D* speed, Vector2D& collVector)
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
	else if (blocksmap->collision(rect, speed, collVector, this))
		collides = true;

	collVector.normalize();
	return collides;
}

// maneja como actuar cuando el jugador pierde una vida
void PlayState::death() {
	ballpos = Vector2D(400, 400);
	if (ballspeed.getY() > 0) {
		ballspeed = Vector2D(ballspeed.getX(), -ballspeed.getY());
	}
	if (lifes > 1) {
		lifes--;
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	}
	// game over
	else
	{
		app->getStateMachine()->pushState(new EndState(app));
		/*
		cout << "GAME OVER" << endl;
		ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
		SDL_Delay(3000);
		currentLevel = 0;
		uint blocksmapW = blocksmap->getW();
		uint blocksmapH = blocksmap->getH();
		arkanoidObjects.remove(blocksmap);
		delete blocksmap;
		blocksmap = new BlocksMap(blocksmapW, blocksmapH, app->getTexture(brickst));
		blocksmap->loadMap("..//maps//" + levels[currentLevel], app->getTexture(brickst));
		arkanoidObjects.push_front(blocksmap);
		lifes = 3;
		*/
	}
	cout << "Lifes: " << lifes << endl;
}

// avanza al siguiente nivel
void PlayState::nextLevel()
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
		blocksmap = new BlocksMap(blocksmapW, blocksmapH, app->getTexture(brickst));
		blocksmap->loadMap("..//maps//" + levels[currentLevel], app->getTexture(brickst));
		arkanoidObjects.push_front(blocksmap);
	}
	ball->resetBall(ballpos, ballspeed.getX(), ballspeed.getY());
	SDL_Delay(500);
}

void PlayState::extraLife()
{
	lifes++;
	cout << "Lifes: " << lifes << endl;
}

void PlayState::killObject(Reward* r)
{
	for (list<ArkanoidObject*>::iterator list = arkanoidObjects.begin(); list != arkanoidObjects.end(); ++list) {
		if ((*list) == r) {
			delete r;
			arkanoidObjects.erase(list);
			break;
		}
	}
}

void PlayState::loadList()
{
	arkanoidObjects.push_back(blocksmap);
	arkanoidObjects.push_back(paddle);
	arkanoidObjects.push_back(ball);
	arkanoidObjects.push_back(leftwall);
	arkanoidObjects.push_back(rightwall);
	arkanoidObjects.push_back(topwall);
}

void PlayState::saveGame()
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

void PlayState::spawnReward(Vector2D pos)
{
	srand(time(NULL));
	uint type = rand() % 4;
	list<ArkanoidObject*>::iterator it = arkanoidObjects.end();
	Reward* powerUp = new Reward(pos, 50, 20, powerUpType[type], Vector2D(0, 2), paddle, app->getTexture(rewardt), this, it);
	arkanoidObjects.push_back(powerUp);
}
