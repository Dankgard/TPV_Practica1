#pragma once

#include "ArkanoidError.h"
#include "checkML.h"


class FileNotFoundError : public ArkanoidError {
protected:

public:
	FileNotFoundError(const string &message) : ArkanoidError("File Not Found: " + message) {}
};
