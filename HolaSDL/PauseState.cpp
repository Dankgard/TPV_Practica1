#include "PauseState.h"

PauseState::PauseState() {
	cout << "PauseState" << endl;
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