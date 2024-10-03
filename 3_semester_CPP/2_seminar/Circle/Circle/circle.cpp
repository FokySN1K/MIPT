#include "circle.h"
#define M_PI   3.14159265358979323846

Circle::Circle() {
	mCenter = { 0,0 };
	mRadius = 1;
}
Circle::Circle(const Point& acentre, float aradius) {
	mCenter = acentre;
	mRadius = aradius;
}
Circle::Circle(const Circle& circle) {
	this->mCenter = circle.mCenter;
	this->mRadius = circle.mRadius;
}

void Circle::setCenter(const Point& center) {
	mCenter = center;
}
void Circle::setRadius(float radius) {
	if (radius < 0) {
		mRadius = 0;
	}
	else {
		mRadius = radius;
	}
}

Point Circle::getCenter() {
	return mCenter;
}
float Circle::getRadius() {
	return mRadius;
}

float Circle::getArea() {
	return M_PI * mRadius * mRadius;
}
float Circle::getDistance(const Point& p) {
	float distance = mCenter.distance(p);
	return abs(mRadius - distance);
}

bool Circle::isColliding(const Circle& c) {
	float distance = mCenter.distance(c.mCenter);
	if (distance < (c.mRadius + mRadius) || c.mRadius > (distance + mRadius) || mRadius > (distance + c.mRadius)) {
		return false;
	}
	return true;
}
void Circle::move(const Point& p) {
	mCenter = mCenter + p;
}