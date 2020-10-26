#include "Vector3.h"
#include <cmath>
using namespace std;

double Vector3::compute_length(double X, double Y, double Z) { return sqrt(x * x + y * y + z * z); };

Vector3::Vector3() : x(0), y(0), z(0), length(0) {};
Vector3::Vector3(double X, double Y, double Z) : x(X), y(Y), z(Z), length(compute_length(X, Y, Z)) {};
double Vector3::X()
{
	return x;
}
void Vector3::SetX(double X)
{
	x = X;
	length = compute_length(x, y, z);
}
double Vector3::Y()
{
	return y;
}
void Vector3::SetY(double Y)
{
	y = Y;
	length = compute_length(x, y, z);
}
double Vector3::Z()
{
	return z;
}
void Vector3::SetZ(double Z)
{
	z = Z;
	length = compute_length(x, y, z);
}
Vector3 Vector3::operator*(const double& scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}
Vector3 Vector3::operator+(const Vector3& V)
{
	return Vector3(x + V.x, y + V.y, z + V.z);
}
void Vector3::operator+=(const Vector3& V)
{
	x += V.x;
	y += V.y;
	z += V.z;
}
Vector3 Vector3::operator-(const Vector3& V)
{
	return Vector3(x - V.x, y - V.y, z - V.z);
}
void Vector3::operator-=(const Vector3& V)
{
	x -= V.x;
	y -= V.y;
	z -= V.z;
}
Vector3 Vector3::Cross(const Vector3& V)
{
	return Vector3(y * V.z - z * V.y, x * V.z - z * V.x, x * V.y - y * V.x);
}
double Vector3::Dot(const Vector3& V)
{
	return x * V.x + y * V.y + z * V.z;
}
double Vector3::Length() { return length; };
Vector3 Vector3::Normalized() { return Vector3(x / length, y / length, z / length); }
double Vector3::DistanceToPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal)
{
	return (*this - PlaneOrigin).Dot(PlaneNormal);
}
Vector3 Vector3::ProjectOnPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal)
{
	return *this - PlaneNormal * DistanceToPlane(PlaneOrigin, PlaneNormal);
}

istream& operator>>(istream& in, Vector3& V)
{
	double x, y, z;
	in >> x >> y >> z;
	V = Vector3(x, y, z);
	return in;
}

ostream& operator<<(ostream& out, Vector3 V)
{
	out << "(" << V.X() << ", " << V.Y() << ", " << V.Z() << ")";
	return out;
}
