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
	
	Texture* Play;
	
	Texture* Load;
	
	Texture* exitB;

	bool exit = false;
public:
	Menu();
	~Menu();
	void run();
	void update();
	void render();
	void handleEvents();
};