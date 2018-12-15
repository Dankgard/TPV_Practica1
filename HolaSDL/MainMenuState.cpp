#include "MainMenuState.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update() 
{

}

void MainMenuState::render()
{

}

bool MainMenuState::onEnter()
{
	cout << "Entrar Menu" << endl;
	return true;
}

bool MainMenuState::onExit()
{
	cout << "Salir Menu" << endl;
	return true;
}