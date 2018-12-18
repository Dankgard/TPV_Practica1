
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "SdlApplication.h"

using namespace std;

using uint = unsigned int;


int main(int argc, char* argv[]){
	SdlApplication app = SdlApplication();
	app.run();
	return 0;
}