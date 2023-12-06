//
// Created by gibbs2b on 18/06/23.
//

#include "matrix4f.h"
#include "vector3f.h"

matrix4f::matrix4f() {
    setIdentity();
}

void matrix4f::set(int row, int col, float value) {
    matrix[row + col * 4] = value;
}

float matrix4f::get(int row, int col) {
    return matrix[row + col * 4];
}

void matrix4f::setIdentity() {
    for (int i = 0; i < 16; i++) {
        matrix[i] = 0.0f;
    }

    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

matrix4f matrix4f::identity() {
    matrix4f result;
    return result;
}

matrix4f matrix4f::translateTo(float x, float y, float z) {
    matrix4f result = *this;
    result[12] = x;
    result[13] = y;
    result[14] = z;
    return result;
}

matrix4f matrix4f::translateBy(float x, float y, float z) {
    matrix4f result = *this;
    result[12] += x;
    result[13] += y;
    result[14] += z;
    return result;
}

matrix4f matrix4f::translate(float x, float y, float z) {
    matrix4f result;
    result[12] = x;
    result[13] = y;
    result[14] = z;
    return result;
}

matrix4f matrix4f::scale(float x, float y, float z) {
    matrix4f result;
    result[0] = x;
    result[5] = y;
    result[10] = z;
    return result;
}

matrix4f matrix4f::scaleBy(float x, float y, float z) {
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

matrix4f matrix4f::ortho(float left, float right, float bottom, float top, float near, float far) {
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

matrix4f
matrix4f::ortho_rectangle(float sx1, float sy1, float sx2, float sy2, float tx1, float ty1, float tx2, float ty2) {
    matrix4f result;
    result[0] = (tx2 - tx1) / (sx2 - sx1);
    result[5] = (ty2 - ty1) / (sy2 - sy1);
    result[10] = 1.0f;
    result[12] = tx1 - result[0] * sx1;
    result[13] = ty1 - result[5] * sy1;
    result[15] = 1.0f;
    return result;
}

float &matrix4f::operator[](int i) {
    return matrix[i];
}

const float &matrix4f::operator[](int i) const {
    return matrix[i];
}

void matrix4f::operator=(const matrix4f &other) {
    for (int i = 0; i < 16; i++) {
        matrix[i] = other[i];
    }
}

matrix4f matrix4f::operator*(const matrix4f &other) {
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

Vector3f matrix4f::operator*(const Vector3f &other) {
    Vector3f result;

    result.x = matrix[0] * other.x + matrix[4] * other.y + matrix[8] * other.z + matrix[12];
    result.y = matrix[1] * other.x + matrix[5] * other.y + matrix[9] * other.z + matrix[13];
    result.z = matrix[2] * other.x + matrix[6] * other.y + matrix[10] * other.z + matrix[14];

    return result;
}
