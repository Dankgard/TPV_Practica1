#include "PlayState.h"


PlayState::PlayState(SdlApplication* app): GameState(app)
{
	cout << app;
};

PlayState::~PlayState()
{

}


void PlayState::render()
{
	SDL_Rect dstRect;
	dstRect.x = 100;
	dstRect.y = 100;
	dstRect.w = 300;
	dstRect.h = 300;
	Texture* texture = app->getTexture(2);
	texture->render(dstRect, SDL_FLIP_NONE);
}

bool PlayState::handleEvents(SDL_Event& event)
{	
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
		app->getStateMachine()->pushState(new PauseState(app));
	}
	else
	{
		GameState::handleEvents(event);
	}
	return true;
}
