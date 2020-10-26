#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {};

Vector2::Vector2(double X, double Y) : x(X), y(Y) {};

double Vector2::X()
{
	return x;
}

void Vector2::SetX(double X)
{
	x = X;
}

double Vector2::Y()
{
	return y;
}

void Vector2::SetY(double Y)
{
	y = Y;
}

Vector2 Vector2::operator*(const double& scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator+(const Vector2& V)
{
	return Vector2(x + V.x, y + V.y);
}

void Vector2::operator+=(const Vector2& V)
{
	x += V.x;
	y += V.y;
}

Vector2 Vector2::operator-(const Vector2& V)
{
	return Vector2(x - V.x, y - V.y);
}

void Vector2::operator-=(const Vector2& V)
{
	x -= V.x;
	y -= V.y;
}

double Vector2::Cross(const Vector2& V)
{
	return x * V.y - V.x * y;
}

std::istream& operator>>(std::istream& in, Vector2& V)
{
	double x, y;
	in >> x >> y;
	V = Vector2(x, y);
	return in;
}

std::ostream& operator<<(std::ostream& out, Vector2 V)
{
	out << "(" << V.X() << ", " << V.Y() << ")";
	return out;
}
