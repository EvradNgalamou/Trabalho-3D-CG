//
// Created by gibbs2b on 18/06/23.
//

#ifndef README_MD_MATRIX4F_H
#define README_MD_MATRIX4F_H


#include "vector3f.h"

struct matrix4f {
    // column-major order
    // m0 m4 m8  m12
    // m1 m5 m9  m13
    // m2 m6 m10 m14
    // m3 m7 m11 m15
    float matrix[16];

    matrix4f() {
        setIdentity();
    }

    void set(int row, int col, float value) {
        matrix[row + col * 4] = value;
    }

    float get(int row, int col) {
        return matrix[row + col * 4];
    }

    void setIdentity() {
        for (int i = 0; i < 16; i++) {
            matrix[i] = 0.0f;
        }

        matrix[0] = 1.0f;
        matrix[5] = 1.0f;
        matrix[10] = 1.0f;
        matrix[15] = 1.0f;
    }

    static matrix4f identity() {
        matrix4f result;
        return result;
    }

    matrix4f translateTo(float x, float y, float z) {
        matrix4f result = *this;
        result[12] = x;
        result[13] = y;
        result[14] = z;
        return result;
    }

    matrix4f translateBy(float x, float y, float z) {
        matrix4f result = *this;
        result[12] += x;
        result[13] += y;
        result[14] += z;
        return result;
    }

    static matrix4f translate(float x, float y, float z) {
        matrix4f result;
        result[12] = x;
        result[13] = y;
        result[14] = z;
        return result;
    }

    static matrix4f scale(float x, float y, float z) {
        matrix4f result;
        result[0] = x;
        result[5] = y;
        result[10] = z;
        return result;
    }

    matrix4f scaleBy(float x, float y, float z) {
        matrix4f result = *this;

        result[0] *= x;
        result[1] *= x;
        result[2] *= x;
        result[3] *= x;

        result[4] *= y;
        result[5] *= y;
        result[6] *= y;
        result[7] *= y;

        result[8] *= z;
        result[9] *= z;
        result[10] *= z;
        result[11] *= z;

        return result;
    }

    static matrix4f ortho(float left, float right, float bottom, float top, float near, float far) {
        matrix4f result;
        result[0] = 2.0f / (right - left);
        result[5] = 2.0f / (top - bottom);
        result[10] = -2.0f / (far - near);
        result[12] = -(right + left) / (right - left);
        result[13] = -(top + bottom) / (top - bottom);
        result[14] = -(far + near) / (far - near);
        result[15] = 1.0f;
        return result;
    }

    static matrix4f ortho_rectangle(
            float sx1, float sy1, float sx2, float sy2,
            float tx1, float ty1, float tx2, float ty2
    ) {
        matrix4f result;
        result[0] = (tx2 - tx1) / (sx2 - sx1);
        result[5] = (ty2 - ty1) / (sy2 - sy1);
        result[10] = 1.0f;
        result[12] = tx1 - result[0] * sx1;
        result[13] = ty1 - result[5] * sy1;
        result[15] = 1.0f;
        return result;
    }

    // [i]
    float &operator[](int i) {
        return matrix[i];
    }

    // [i]
    const float &operator[](int i) const {
        return matrix[i];
    }

    // m[i]=v
    void operator=(const matrix4f &other) {
        for (int i = 0; i < 16; i++) {
            matrix[i] = other[i];
        }
    }

    // matrix multiplication
    matrix4f operator*(const matrix4f &other) {
        matrix4f result;

        for (int i = 0; i < 4; i++) {
            result[i] = matrix[i] * other[0] + matrix[i + 4] * other[1] + matrix[i + 8] * other[2] +
                        matrix[i + 12] * other[3];
            result[i + 4] = matrix[i] * other[4] + matrix[i + 4] * other[5] + matrix[i + 8] * other[6] +
                            matrix[i + 12] * other[7];
            result[i + 8] = matrix[i] * other[8] + matrix[i + 4] * other[9] + matrix[i + 8] * other[10] +
                            matrix[i + 12] * other[11];
            result[i + 12] = matrix[i] * other[12] + matrix[i + 4] * other[13] + matrix[i + 8] * other[14] +
                             matrix[i + 12] * other[15];
        }

        return result;
    }
};


#endif //README_MD_MATRIX4F_H
