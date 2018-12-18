#include "PauseState.h"

PauseState::PauseState(SdlApplication* app) : GameState(app) {

}

PauseState::~PauseState() {

}

void PauseState::update() {
	GameState::update();
}

void PauseState::render() {
	GameState::render();
}

void PauseState::handleEvent() {

}