#pragma once

#include "ArkanoidError.h"
#include "checkML.h"

class SDLError : public ArkanoidError {
protected:

public:
	SDLError(const string &message) : ArkanoidError("SDL Error: " + message) {}
};
