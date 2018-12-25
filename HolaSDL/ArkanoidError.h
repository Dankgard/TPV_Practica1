#pragma once

#include <exception>
#include <string>
#include <stdexcept>
#include "checkML.h"
using namespace std;

class ArkanoidError : public logic_error {
protected:

public:
	ArkanoidError(const string &message) : logic_error("Arkanoid Error " + message) {}
};