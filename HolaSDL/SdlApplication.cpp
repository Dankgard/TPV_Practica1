#include "SdlApplication.h"

SdlApplication::SdlApplication() {
	cout << "SdlApplication" << endl;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	gameStates[menu] = new MainMenuState(this);
	gameStates[play] = new PlayState(this);
	gameStates[pause] = new PauseState(this);
	gameStates[end] = new EndState(this);

	state = new GameStateMachine();
	state->pushState(gameStates[menu]);
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
