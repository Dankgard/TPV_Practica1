
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Menu.h"
#include "Game.h"

using namespace std;

using uint = unsigned int;


int main(int argc, char* argv[]){
	Menu menu = Menu();
	menu.run();
	return 0;
}