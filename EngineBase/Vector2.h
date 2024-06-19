#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <iostream>
//2D�x�N�g��
struct Vector2
{
    float x, y;

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // Addition
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2& operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    // Subtraction
    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2& operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2 operator*(const Vector2& v) const {
        return Vector2(x * v.x, y * v.y);
    }

    Vector2 operator*=(const Vector2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    // Scalar multiplication
    Vector2 operator*(const float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // �x�N�g���̑傫���i�����j���v�Z���܂��B
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // �x�N�g���𐳋K�����܂�
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag == 0) return Vector2(0, 0);
        return Vector2(x / mag, y / mag);
    }

    // �x�N�g���̓���
    float dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    //�����̌v�Z
    float distance(const Vector2& v) const {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }

    //2�̃x�N�g���̊Ԃ̊p�x
    float angleBetween(const Vector2& v) const {
        float dotProd = dot(v);
        float magProd = magnitude() * v.magnitude();
        return std::acos(dotProd / magProd); // ���W�A���P�ʂ̊p�x
    }

    //�x�N�g���̐��^���
    Vector2 lerp(const Vector2& v, float t) const {
        return *this + (v - *this) * t;
    }

    // Static method to return a zero vector
    static Vector2 Zero() {
        return Vector2(0.0f, 0.0f);
    }

    static Vector2 One() {
        return Vector2(1.0f, 1.0f);
    }
};
static std::ostream& operator<<(std::ostream& out, const Vector2& vec)
{
    std::cout << "(" << vec.x << "," << vec.y << ")";
    return out;
}
#endif // !_VECTOR2_H_




