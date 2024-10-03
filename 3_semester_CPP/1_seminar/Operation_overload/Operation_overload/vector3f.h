#pragma once
#include <iostream>
using namespace std;

struct Vector3f {
	float x, y, z;
};
ostream& operator<<(ostream& out, const Vector3f& a);
istream& operator>>(istream& in, Vector3f& a);
Vector3f operator +(const Vector3f& a, const Vector3f& b);
Vector3f operator -(const Vector3f& a, const Vector3f& b);
Vector3f operator *(const Vector3f& a, float b);
Vector3f operator *(float b, Vector3f& a);
float operator *(const Vector3f& a, const Vector3f& b);
Vector3f operator /(const Vector3f& a, float b);
Vector3f operator +(const Vector3f& a);
Vector3f operator -(const Vector3f& a);
bool operator==(const Vector3f& a, const Vector3f& b);
bool operator!=(const Vector3f& a, const Vector3f& b);
Vector3f operator +=(Vector3f& a, const Vector3f& b);
Vector3f operator -=(Vector3f& a, const Vector3f& b);
Vector3f operator *=(Vector3f& a, float b);
Vector3f operator /=(Vector3f& a, float b);
float squared_norm(const Vector3f& a);
float norm(const Vector3f& a);
void normalize(Vector3f& a);