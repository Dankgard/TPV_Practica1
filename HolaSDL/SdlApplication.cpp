#include "SdlApplication.h"

SdlApplication::SdlApplication() {
	cout << "SdlApplication" << endl;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	

	textures[0] = new Texture(renderer);
	textures[0]->load("..\\images\\Play.png", 1, 1);
	textures[1] = new Texture(renderer);
	textures[1]->load("..\\images\\Exit.png", 1, 1);
	textures[2] = new Texture(renderer);
	textures[2]->load("..\\images\\Title.png", 1, 1);
	textures[3] = new Texture(renderer);
	textures[3]->load("..\\images\\paddle.png", 1, 1);
	textures[4] = new Texture(renderer);
	textures[4]->load("..\\images\\Load.png", 1, 1);

	state = new GameStateMachine();
	state->pushState(new MainMenuState(this));
}

SdlApplication::~SdlApplication() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gsm = nullptr;

	SDL_Quit();
};

void SdlApplication::run() {
	while (!exit) {
		render();
		handleEvents();
		state->getCurrentState()->update();
	}
}

void SdlApplication::render() {
	if (window == nullptr || renderer == nullptr)
		cout << "Error al cargar" << endl;
	else {
		SDL_RenderClear(renderer);
		state->getCurrentState()->render();
		SDL_RenderPresent(renderer);
	}
}

void SdlApplication::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e) && !exit) {
		if (e.type == SDL_QUIT) {
			exit = true;
		}
		else {
			state->getCurrentState()->handleEvents(e);
		}
	}
}

GameStateMachine* SdlApplication::getStateMachine() {
	return state;
}

Texture* SdlApplication::getTexture(int texture) {	
	return textures[texture];
}
