//
// Created by gibbs2b on 18/06/23.
//

#ifndef README_MD_VECTOR2F_HPP
#define README_MD_VECTOR2F_HPP

#include "igl.h"

struct Vector3f {
    float x, y, z;

    Vector3f(float x, float y, float z);

    Vector3f(float* f);

    Vector3f();

    Vector3f(unsigned int x, unsigned int y, unsigned int z);

    Vector3f(int x, int y, int z);

    Vector3f operator+(const Vector3f &other) const;

    // add a scalar to each component
    Vector3f operator+(float scalar) const;

    // +=
    Vector3f &operator+=(const Vector3f &other);

    Vector3f operator-(const Vector3f &other) const;

    Vector3f operator-(float scalar) const;

    // -=
    Vector3f &operator-=(const Vector3f &other);

    Vector3f operator*(float scalar) const;

    Vector3f operator/(float scalar) const;

    Vector3f operator/(const Vector3f &other) const;

    float* ptr();

    float lengthSqr() const;

    float length2() const;

    float length() const;

    float dot(const Vector3f &other) const;

    Vector3f cross(const Vector3f &other) const;

    void normalize();

    Vector3f projectOnto(const Vector3f &axis) const;

    void getProjectionAndComplement(const Vector3f &axis, Vector3f &projection, Vector3f &complement) const;
};

#endif //README_MD_VECTOR2F_HPP
