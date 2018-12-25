#pragma once

#include "ArkanoidError.h"
#include "checkML.h"


class FileFormatError : public ArkanoidError {
protected:

public:
	FileFormatError(const string &message) : ArkanoidError("File Format: " + message) {}
};
