#pragma once
#include "point.h"
#include <iostream>
#include <cmath>
using namespace std;


class Circle
{
private:
	Point mCenter;
	float mRadius;

public:
	Circle();
	Circle(const Point& acentre, float aradius);
	Circle(const Circle& circle);

	void setCenter(const Point& center);
	void setRadius(float radius);

	Point getCenter();
	float getRadius();

	float getArea();
	float getDistance(const Point& p);

	bool isColliding(const Circle& c);
	void move(const Point& p);

};