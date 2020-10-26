#pragma once
#include "Shape.h"

class Camera
{
private:

	Vector3 position, orientation;
	int resX, resY;
	Shape* shapes;
	int shape_count;
	char** data;
	

	const static char* CharacterSet;
	const static int CharacterCount;

	void draw_triangle(Triangle T, double dot);

public:
	Camera(Shape* Shapes, int ShapeCount, Vector3 Position = Vector3(), Vector3 Orientation = Vector3(1, 0, 0), int ResX = 50, int ResY = 50);

	int ResX() const;
	int ResY() const;

	void Render();

	friend std::ostream& operator<< (std::ostream& out, const Camera& C);
	~Camera();

};

