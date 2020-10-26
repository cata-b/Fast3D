#include "Camera.h"
#include "Vector2.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <tuple>
using namespace std;

const char* Camera::CharacterSet = new char[65]{ ".'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao#MW8B" };
const int Camera::CharacterCount = 64;

void Camera::draw_triangle(Triangle T, double dot)
{
	dot = dot * CharacterCount;
	auto v1 = Vector2(T[0].X() + position.X() + resX / 2, T[0].Y() + position.Y() + resY / 2),
		v2 = Vector2(T[1].X() + position.X() + resX / 2, T[1].Y() + position.Y() + resY / 2),
		v3 = Vector2(T[2].X() + position.X() + resX / 2, T[2].Y() + position.Y() + resY / 2);
	double maxX = max(v1.X(), max(v2.X(), v3.X()));
	double minX = min(v1.X(), min(v2.X(), v3.X()));
	double maxY = max(v1.Y(), max(v2.Y(), v3.Y()));
	double minY = min(v1.Y(), min(v2.Y(), v3.Y()));
	Vector2 vs1 = v2 - v1;
	Vector2 vs2 = v3 - v1;

	maxY = (maxY > resY ? (double)resY - 1 : maxY);
	minY = (minY < 0 ? 0 : minY);
	maxX = (maxX > resX ? (double)resX - 1 : maxX);
	minX = (minX < 0 ? 0 : minX);

	for (int x = (int)minX; x <= maxX; x++)
	{
		for (int y = (int)minY; y <= maxY; y++)
		{
			Vector2 q = Vector2(x - v1.X(), y - v1.Y());

			double s = q.Cross(vs2) / vs1.Cross(vs2);
			double t = vs1.Cross(q) / vs1.Cross(vs2);

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				data[y][x] = CharacterSet[(int)dot];
			}
		}
	}
}

Camera::Camera(Shape* Shapes, int ShapeCount, Vector3 Position, Vector3 Orientation, int ResX, int ResY)
	:
	shapes(Shapes),
	shape_count(ShapeCount),
	position(Position),
	orientation(Orientation),
	resX(ResX),
	resY(ResY)
{
	data = new char* [ResY--];
	for (; ResY > -1; ResY--)
	{
		data[ResY] = new char[ResX + 1];
	}
}

int Camera::ResX() const
{
	return resX;
}

int Camera::ResY() const
{
	return resY;
}

void Camera::Render()
{
	for (size_t i = 0; i < (size_t)resY; i++)
		for (size_t j = 0; j < (size_t)resX; j++)
			data[i][j] = ' ';
	for (size_t i = 0; i < (size_t)shape_count; i++)
	{
		Triangle* faces;
		double* dots;
		size_t size;
		std::tie(faces, dots, size) = shapes[i].FacesFacing(orientation);
		for (size_t j = 0; j < (size_t)size; j++)
		{
			auto projection = faces[j].ProjectOnPlane(position, orientation);
			// rn the camera should only look along the z axis, so just flatten that
			//TODO: rotate points to get coordinates on the screen (in order to place the camera anywhere)
			draw_triangle(projection, dots[j]);
		}
		delete[] dots;
		delete[] faces;
		for (size_t i = 0; i < (size_t)resY; i++)
			data[i][resX] = 0;
	}
}

Camera::~Camera()
{
	if (data != nullptr)
	{
		for (size_t i = 0; i < (size_t)resY; i++)
			delete[] data[i];
		delete[] data;
		data = nullptr;
	}
	if (shapes != nullptr)
	{
		delete[] shapes;
		shapes = nullptr;
	}
}

ostream& operator<<(ostream& out, const Camera& C)
{
	ostringstream out_s;
	for (int i = C.ResY() - 1; i > -1; i -= 2, out_s << "\n")
		out_s << C.data[i];
	out << out_s.str() << "\n";
	return out;
}
