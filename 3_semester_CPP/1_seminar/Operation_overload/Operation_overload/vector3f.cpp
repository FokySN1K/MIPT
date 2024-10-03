#include "vector3f.h"

ostream& operator<<(ostream& out, const Vector3f& a) {
    out << '{' << a.x << ", " << a.y << ", " << a.z << '}' << endl;
    return out;
}
istream& operator>>(istream& in, Vector3f& a) {
    in >> a.x >> a.y >> a.z;
    return in;
}
Vector3f operator +(const Vector3f& a, const Vector3f& b) {
    Vector3f result = { a.x + b.x, a.y + b.y, a.z + b.z };
    return result;
}
Vector3f operator -(const Vector3f& a, const Vector3f& b) {
    Vector3f result = { a.x - b.x, a.y - b.y, a.z - b.z };
    return result;
}
Vector3f operator *(const Vector3f& a, float b) {
    Vector3f result = { a.x * b, a.y * b, a.z * b };
    return result;
}
Vector3f operator *(float b, Vector3f& a) {
    Vector3f result = { a.x * b, a.y * b, a.z * b };
    return result;
}
float operator *(const Vector3f& a, const Vector3f& b) {
    float result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}
Vector3f operator /(const Vector3f& a, float b) {
    Vector3f result = { a.x / b, a.y / b, a.z / b };
    return result;
}
Vector3f operator +(const Vector3f& a) {
    Vector3f result = { a.x, a.y, a.z };
    return result;
}
Vector3f operator -(const Vector3f& a) {
    Vector3f result = { -a.x, -a.y, -a.z };
    return result;
}
bool operator==(const Vector3f& a, const Vector3f& b) {
    if (a.x == b.x && a.y == b.y && a.z == b.z) {
        return 1;
    }
    return 0;
}
bool operator!=(const Vector3f& a, const Vector3f& b) {
    if (a.x != b.x || a.y != b.y || a.z != b.z) {
        return 1;
    }
    return 0;
}
Vector3f operator +=(Vector3f& a, const Vector3f& b) {
    a = { a.x + b.x, a.y + b.y, a.z + b.z };
    return a;
}
Vector3f operator -=(Vector3f& a, const Vector3f& b) {
    a = { a.x - b.x, a.y - b.y, a.z - b.z };
    return a;
}
Vector3f operator *=(Vector3f& a, float b) {
    a = { a.x * b, a.y * b, a.z * b };
    return a;
}
Vector3f operator /=(Vector3f& a, float b) {
    a = { a.x / b, a.y / b, a.z / b };
    return a;
}
float squared_norm(const Vector3f& a) {
    float normal = a.x * a.x + a.y * a.y + a.z * a.z;
    return normal;
}
float norm(const Vector3f& a) {
    return sqrt(squared_norm(a));
}
void normalize(Vector3f& a) {
    float normal = norm(a);
    a = { a.x / normal, a.y / normal , a.z / normal };
}