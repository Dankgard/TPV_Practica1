#include "GameState.h"


void GameState::render() {
	for (list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();) {
		((*it++))->render();
	}
}

void GameState::update() {
	for (list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();) {
		((*it++))->update();
	}
}

void GameState::handleEvents(SDL_Event event) {
	for (list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();) {
		((*it++))->handleEvents(event);
	}
}