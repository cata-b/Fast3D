#include "Triangle.h"

Triangle::Triangle() : vertices(nullptr) {}

Triangle::Triangle(Vector3* Vertices) : vertices(Vertices) {}

Triangle::Triangle(const Triangle& other)
{
	vertices = new Vector3[3];
	for (int i = 0; i < 3; i++)
		vertices[i] = other.vertices[i];
}

const Triangle& Triangle::operator=(Triangle&& other) noexcept
{
	vertices = other.vertices;
	other.vertices = nullptr;
	return *this;
}

Vector3 Triangle::Normal() const
{ 
	auto v2 = vertices[2], v1 = vertices[1], v0 = vertices[0];
	return Vector3((v2 - v1).Cross(v1 - v0)).Normalized();
}

Vector3 Triangle::Center() const
{
	Vector3 center(0, 0, 0);
	for (size_t i = 0; i < (size_t)3; i++)
		center += vertices[i];
	center = center * ((double)1 / 3);
	return center;
}

Vector3& Triangle::operator[](size_t index)
{
	return vertices[index];
}

Triangle Triangle::ProjectOnPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal)
{
	Vector3* result = new Vector3[3];
	for (size_t i = 0; i < (size_t)3; i++)
		result[i] = vertices[i].ProjectOnPlane(PlaneOrigin, PlaneNormal);
	return Triangle(result);
}

Triangle::~Triangle()
{
	if (vertices == nullptr)
		return;
	delete[] vertices;
	vertices = nullptr;
}
