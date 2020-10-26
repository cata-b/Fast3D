#pragma once
#include "Triangle.h"

class Shape
{
private:
	Vector3 origin;
	Triangle* faces;
	int face_count;
public:
	Shape();
	Shape(Vector3 Origin, Triangle* Faces, int FaceCount);
	std::tuple<Triangle*, double*, size_t> FacesFacing(Vector3 Direction) const;
	const Shape& operator= (Shape&& other) noexcept;
	double OriginDistanceToPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal);
	void RotateX(double theta);
	void RotateY(double theta);
	void RotateZ(double theta);

	~Shape();
};