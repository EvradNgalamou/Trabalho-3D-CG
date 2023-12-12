#include <cmath>
#include "vector3f.h"

float Vector3f::length() const {
    return sqrtf(lengthSqr());
}

float Vector3f::dot(const Vector3f &other) const {
    return x * other.x + y * other.y + z * other.z;
}

void Vector3f::normalize() {
    float len = length();
    x /= len;
    y /= len;
    z /= len;
}

Vector3f Vector3f::projectOnto(const Vector3f &axis) const {
    return axis * (dot(axis) / axis.lengthSqr());
}

float Vector3f::length2() const {
    return lengthSqr();
}

Vector3f Vector3f::operator/(const Vector3f &other) const {
    return Vector3f(x / other.x, y / other.y, z / other.z);
}

float* Vector3f::ptr() {
    return &x;
}

float Vector3f::lengthSqr() const {
    return x * x + y * y + z * z;
}

Vector3f Vector3f::operator/(float scalar) const {
    return Vector3f(x / scalar, y / scalar, z / scalar);
}

Vector3f Vector3f::operator*(float scalar) const {
    return Vector3f(x * scalar, y * scalar, z * scalar);
}

Vector3f &Vector3f::operator-=(const Vector3f &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3f Vector3f::operator-(float scalar) const {
    return Vector3f(x - scalar, y - scalar, z - scalar);
}

Vector3f Vector3f::operator-(const Vector3f &other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f &Vector3f::operator+=(const Vector3f &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3f Vector3f::operator+(float scalar) const {
    return Vector3f(x + scalar, y + scalar, z + scalar);
}

Vector3f Vector3f::operator+(const Vector3f &other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f::Vector3f(int x, int y, int z) : x((float) x), y((float) y), z((float) z) {}

Vector3f::Vector3f(unsigned int x, unsigned int y, unsigned int z) : x((float) x), y((float) y), z((float) z) {}

Vector3f::Vector3f() : x(0), y(0), z(0) {}

Vector3f::Vector3f(float* f) : x(f[0]), y(f[1]), z(f[2]) {}

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

void Vector3f::getProjectionAndComplement(const Vector3f &axis, Vector3f &projection, Vector3f &complement) const {
    projection = projectOnto(axis);
    complement = *this - projection;
}

Vector3f Vector3f::cross(const Vector3f &other) const {
    return Vector3f(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
    );
}

Vector3f Vector3f::operator-() const {
    return Vector3f(-x, -y, -z);
}
