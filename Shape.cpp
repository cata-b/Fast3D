#include "Shape.h"
#include <tuple>
#define PI 3.14159265
using namespace std;

Shape::Shape() : origin(0, 0, 0), faces(nullptr), face_count(0) {}

Shape::Shape(Vector3 Origin, Triangle* Faces, int FaceCount) : origin(Origin), faces(Faces), face_count(FaceCount) {}

std::tuple<Triangle*, double*, size_t> Shape::FacesFacing(Vector3 Direction) const
{
	auto result_faces = new Triangle[face_count];
	auto dots = new double[face_count];
	size_t size = 0;
	for (size_t i = 0; i < (size_t)face_count; i++)
	{
		auto& face = faces[i];
		double dot = Direction.Dot(face.Normal());
		if (dot > 0)
		{
			result_faces[size] = std::move(Triangle(face));
			dots[size] = dot;
			size++;
		}
	}
	return make_tuple(result_faces, dots, size);
}

const Shape& Shape::operator=(Shape&& other) noexcept
{
	faces = other.faces;
	other.faces = nullptr;
	face_count = other.face_count;
	origin = other.origin;
	return *this;
}

double Shape::OriginDistanceToPlane(const Vector3& PlaneOrigin, const Vector3& PlaneNormal)
{
	return origin.DistanceToPlane(PlaneOrigin, PlaneNormal);
}

void Shape::RotateX(double theta)
{
	for (size_t i = 0; i < (size_t)face_count; i++)
	{
		auto& face = faces[i];
		for (size_t j = 0; j < (size_t)3; j++)
		{
			auto& vertex = face[j];
			double ct = cos(theta * PI / 180), st = sin(theta * PI / 180);
			double y = vertex.Y() * ct - vertex.Z() * st,
				z = vertex.Y() * st + vertex.Z() * ct;
			vertex.SetY(y);
			vertex.SetZ(z);
		}
	}
}

void Shape::RotateY(double theta)
{
	for (size_t i = 0; i < (size_t)face_count; i++)
	{
		auto& face = faces[i];
		for (size_t j = 0; j < (size_t)3; j++)
		{
			auto& vertex = face[j];
			double ct = cos(theta * PI / 180), st = sin(theta * PI / 180);
			double x = vertex.X() * ct + vertex.Z() * st,
				z = -vertex.X() * st + vertex.Z() * ct;
			vertex.SetX(x);
			vertex.SetZ(z);
		}
	}
}

void Shape::RotateZ(double theta)
{
	for (size_t i = 0; i < (size_t)face_count; i++)
	{
		auto& face = faces[i];
		for (size_t j = 0; j < (size_t)3; j++)
		{
			auto& vertex = face[j];
			double ct = cos(theta * PI / 180), st = sin(theta * PI / 180);
			double x = (vertex.X() * ct - vertex.Y() * st),
				y = (vertex.X() * st + vertex.Y() * ct);
			vertex.SetX(x);
			vertex.SetY(y);
		}
	}
}

Shape::~Shape()
{
	if (faces == nullptr)
		return;
	delete[] faces;
	faces = nullptr;
}
