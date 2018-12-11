#include "Menu.h"
#include "Game.h"
#include "Texture.h"
#include "checkML.h"

Menu::Menu() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		MENU_WIDTH, MENU_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
	
	/*/Rect/*/
	//Titulo
	titlerect.x = 100;
	titlerect.y = 50;
	titlerect.w = 700;
	titlerect.h = 200;

	//BotonPlay
	PlayRect.x = 100;
	PlayRect.y = 425;
	PlayRect.w = 100;
	PlayRect.h = 100;

	//Load
	LoadRect.x = 350;
	LoadRect.y = 425;
	LoadRect.w = 100;
	LoadRect.h = 100;

	//End
	exitRect.x = 600;
	exitRect.y = 425;
	exitRect.w = 100;
	exitRect.h = 100;

	/*/Texture/*/

	//Titulo
	Title = new Texture(renderer);
	Title->load("..\\images\\Title.png", 1, 1);

	//Play
	Play = new Texture(renderer);
	Play->load("..\\images\\Play.png", 1, 1);

	//Load
	Load = new Texture(renderer);
	Load->load("..\\images\\Load.png", 1, 1);

	exitB = new Texture(renderer);
	exitB->load("..\\images\\Exit.png", 1, 1);
}

Menu::~Menu() {
	// destruye los punteros
	delete Play;
	Play = nullptr;
	delete exitB;
	exitB = nullptr;
	delete Load;
	Load = nullptr;
	delete Title;
	Title = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Menu::run() {
	while (!exit) {
		handleEvents();
		//update();
		render();
	}
}

void Menu::render() {
	SDL_RenderClear(renderer);
	Title->render(titlerect, SDL_FLIP_NONE);
	Play->render(PlayRect);
	Load->render(LoadRect);
	exitB->render(exitRect);
	SDL_RenderPresent(renderer);
}
void Menu::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;		

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			int x = event.button.x;
			int y = event.button.y;

			if ((x > 100) && (x < 200) && (y > 425) && (y < 525)) 
			{
				Game game = Game();
				game.run();
				exit = true;				
			}

			if ((x > 350) && (x < 450) && (y > 425) && (y < 525))
			{
				string loadCode;
				cout << "Introduzca la partida guardada: " << loadCode;
				cin >> loadCode;				
				Game game = Game(loadCode);
				game.run();
				exit = true;
			}

			if ((x > 600) && (x < 700) && (y > 425) && (y < 525))
			{
				cout << "Salir.";
				exit = true;
			}
		}
	}
}