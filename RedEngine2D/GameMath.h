#pragma once
#ifndef GAME_MATH
#define GAME_MATH

#include <cmath>


#define PI 3.141592


class Vec2
{
public:

	Vec2(double x = 0.0f, double y = 0.0f): x(x), y(y) {}

	Vec2& operator=(const Vec2& vec) {
		this->x = vec.x;
		this->y = vec.y;

		return *this;
	}

	double x, y;
};

class Vec3
{
public:

	Vec3(double x = 0.0f, double y = 0.0f,double z = 0.0f) : x(x), y(y), z(z) {}

	Vec3& operator=(const Vec3& vec) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;

		return *this;
	}

	double x, y, z;
};


enum class ShapeType
{
	QUAD,
	CIRCLE
};


class Shape
{
public:

	virtual ShapeType GetShapeType() = 0;
	virtual Vec2 GetScale() = 0;
	virtual ~Shape() {};
};

class Circle : public Shape
{
public:

	ShapeType GetShapeType() { return ShapeType::CIRCLE; }
	Vec2 GetScale() { return Vec2(radius, radius); }

	Circle(double radius) : radius(radius) {}

	double radius;
};

class Quad : public Shape
{
public:

	ShapeType GetShapeType() { return ShapeType::QUAD; }
	Vec2 GetScale() { return size; }

	Quad(Vec2 size) { this->size = size; }

	Vec2 size;
};

static double vectorAngleDeg(double x1, double x2, double y1, double y2)
{
	//calc angle by inverse tangent
	double angle = atan((y2 - y1) / (x2 - x1)) * 180/PI;

	//check quadrant
	//our coordinate system:                        
	//                     
	//    Q2_|_Q1                              
	//    Q3 | Q4         
	//
	// y direction is down

	//first quadrant
	if (x2 >= x1 && y2 < y1)
	{
		angle = angle  + 360.0f;
	}
	//second quadrant
	if (x2 < x1 && y2 < y1)
	{
		angle = angle  + 180.0f;
	}
	//third quadrant
	if (x2 < x1 && y2 >= y1)
	{
		angle = angle + 180.0f;
	}
	//fourth quadrant
	if (x2 >= x1 && y2 > y1)
	{
		//do nothing
	}


	return angle;
}


#endif // !GAME_MATH