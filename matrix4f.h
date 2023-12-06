//
// Created by gibbs2b on 18/06/23.
//

#ifndef README_MD_MATRIX4F_H
#define README_MD_MATRIX4F_H


// #include "vector2f.hpp"
#include "vector3f.h"

struct matrix4f {
    // column-major order
    // m0 m4 m8  m12
    // m1 m5 m9  m13
    // m2 m6 m10 m14
    // m3 m7 m11 m15
    float matrix[16];

    matrix4f();

    void set(int row, int col, float value);

    float get(int row, int col);

    void setIdentity();

    static matrix4f identity();

    matrix4f translateTo(float x, float y, float z);

    matrix4f translateBy(float x, float y, float z);

    static matrix4f translate(float x, float y, float z);

    static matrix4f scale(float x, float y, float z);

    matrix4f scaleBy(float x, float y, float z);

    static matrix4f ortho(float left, float right, float bottom, float top, float near, float far);

    static matrix4f ortho_rectangle(
            float sx1, float sy1, float sx2, float sy2,
            float tx1, float ty1, float tx2, float ty2
    );

    // [i]
    float &operator[](int i);

    // [i]
    const float &operator[](int i) const;

    // m[i]=v
    void operator=(const matrix4f &other);

    // matrix multiplication
    matrix4f operator*(const matrix4f &other);

    // vector multiplication
    Vector3f operator*(const Vector3f &other);
};


#endif //README_MD_MATRIX4F_H
