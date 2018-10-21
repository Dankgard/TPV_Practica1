#pragma once

#include <iostream>
#include "checkML.h"

class Vector2D {
private:
	double x = 0;
	double y = 0;

public:
	Vector2D();
	Vector2D(double x, double y);
	double getX() const;
	double getY()const;
	void normalize();
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	double operator*(const Vector2D& d) const;
	friend std::ostream& operator<<(std::ostream& os,const Vector2D& v);
};

