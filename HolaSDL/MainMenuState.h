#pragma once

#include"GameState.h"
#include "checkML.h"


using namespace std;

class MainMenuState : public GameState 
{
	private:
		static const string s_menuID; //Identificador
	public:
		virtual void update();
		virtual void render();

		virtual bool onEnter();
		virtual bool onExit();

		virtual string getStateID() const { return s_menuID; }
};