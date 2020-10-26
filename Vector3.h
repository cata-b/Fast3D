#pragma once
#include <iostream>
class Vector3
{
private:
	double x, y, z, length;
	double compute_length(double X, double Y, double Z);
public:
	Vector3();
	Vector3(double X, double Y, double Z);

	double X();
	void SetX(double X);
	double Y();
	void SetY(double Y);
	double Z();
	void SetZ(double Z);

	Vector3 operator* (const double& scalar) const;
	Vector3 operator+ (const Vector3& V);
	void operator+= (const Vector3& V);
	Vector3 operator- (const Vector3& V);
	void operator-= (const Vector3& V);
	Vector3 Cross(const Vector3& V);
	double Dot(const Vector3& V);

	double Length();
	Vector3 Normalized();

	friend std::istream& operator>>(std::istream& in, Vector3& V);
	friend std::ostream& operator<<(std::ostream& out, Vector3 V);

	double DistanceToPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal);
	Vector3 ProjectOnPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal);
};
