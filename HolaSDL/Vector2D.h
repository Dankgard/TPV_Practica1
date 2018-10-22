#pragma once

#include <iostream>
#include "checkML.h"

typedef unsigned int uint;

class Vector2D {
private:
	uint x = 0;
	uint y = 0;

public:
	Vector2D();
	Vector2D(uint x, uint y);
	uint getX() const;
	uint getY()const;
	void normalize();
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator*(uint d) const;
	uint operator*(const Vector2D& d) const;
	friend std::ostream& operator<<(std::ostream& os,const Vector2D& v);
};

