#pragma once
#include "Vector3.h"

class Triangle
{
	Vector3* vertices;
public:
	Triangle();
	Triangle(Vector3* Vertices);
	Triangle(const Triangle& other);
	const Triangle& operator=(Triangle&& other) noexcept;
	Vector3 Normal() const;
	Vector3 Center() const;
	Vector3& operator[](size_t index);
	Triangle ProjectOnPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal);
	~Triangle();
};

