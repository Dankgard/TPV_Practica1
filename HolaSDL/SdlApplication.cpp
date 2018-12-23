#include "SdlApplication.h"

SdlApplication::SdlApplication() {
	cout << "SdlApplication" << endl;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WIN_WIDTH, SDL_WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	for (int i = 0;i < SDL_NUM_TEXTURES - 2 ;i++)
	{
		textures[i] = new Texture(renderer);
		textures[i]->load("..\\images\\" + textureFile[i], 1, 1);
	}
	textures[brickst] = new Texture(renderer, "..//images//" + textureFile[brickst], 2, 3);
	textures[rewardt] = new Texture(renderer, "..//images//" + textureFile[rewardt], 10, 8);
	/*
	textures[play] = new Texture(renderer);
	textures[play]->load("..\\images\\Play.png", 1, 1);
	textures[exit] = new Texture(renderer);
	textures[exit]->load("..\\images\\Exit.png", 1, 1);
	textures[title] = new Texture(renderer);
	textures[title]->load("..\\images\\Title.png", 1, 1);
	textures[3] = new Texture(renderer);
	textures[3]->load("..\\images\\paddle.png", 1, 1);
	textures[4] = new Texture(renderer);
	textures[4]->load("..\\images\\Load.png", 1, 1);*/

	state = new GameStateMachine();
	state->pushState(new MainMenuState(this));
}

SdlApplication::~SdlApplication() {
	for (uint i = 0; i < SDL_NUM_TEXTURES; i++)
		delete textures[i];
	delete state;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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

Texture* SdlApplication::getTexture(SDLTextureType type) {
	return textures[type];
}
