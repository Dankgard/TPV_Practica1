#pragma once

#include <iostream>
#include "checkML.h"
#include "MovingObject.h"


class Reward: public MovingObject {
private:
	list<ArkanoidObject>::iterator itList;
public:
	virtual void action() = 0;
	void update();
};