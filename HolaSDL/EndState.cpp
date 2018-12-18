#include "EndState.h"

EndState::EndState(SdlApplication* app) : GameState(app) {

};

void EndState::update() {
	GameState::update();
}

void EndState::render() {
	GameState::render();
}

void EndState::handleEvents() {

}
