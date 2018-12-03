
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Menu.h"
#include "Game.h"

using namespace std;

using uint = unsigned int;


int main(int argc, char* argv[]){
	/*string filename = "save01";
	Game game = Game();
	try {
		game.run();
	}
	catch (string s)
	{
		if (s.empty())
			cout << SDL_GetError;
		else
			cout << s;
	}
	return 0;*/
	Menu menu = Menu();
	menu.run();
	return 0;
}