#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "checkML.h"

const int MENU_WIDTH = 800;
const int MENU_HEIGHT = 600;

class Menu {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	Texture* Title;
	SDL_Rect titlerect;
	
	Texture* Play;
	SDL_Rect PlayRect;
	
	Texture* Load;
	SDL_Rect LoadRect;
	
	Texture* exitB;
	SDL_Rect exitRect;

	bool exit = false;
public:
	Menu();
	~Menu();
	void run();
	//void update();
	void render();
	void handleEvents();
};