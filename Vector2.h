#pragma once
#include <iostream>
class Vector2
{
private:
	double x, y;
public:
	Vector2();
	Vector2(double X, double Y);

	double X();
	void SetX(double X);
	double Y();
	void SetY(double Y);

	Vector2 operator* (const double& scalar) const;
	Vector2 operator+ (const Vector2& V);
	void operator+= (const Vector2& V);
	Vector2 operator- (const Vector2& V);
	void operator-= (const Vector2& V);

	friend std::istream& operator>>(std::istream& in, Vector2& V);
	friend std::ostream& operator<<(std::ostream& out, Vector2 V);

	double Cross(const Vector2& V);
};


