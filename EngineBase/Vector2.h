#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <iostream>
//2Dベクトル
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

    // ベクトルの大きさ（長さ）を計算します。
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // ベクトルを正規化します
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag == 0) return Vector2(0, 0);
        return Vector2(x / mag, y / mag);
    }

    // ベクトルの内積
    float dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    //距離の計算
    float distance(const Vector2& v) const {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }

    //2つのベクトルの間の角度
    float angleBetween(const Vector2& v) const {
        float dotProd = dot(v);
        float magProd = magnitude() * v.magnitude();
        return std::acos(dotProd / magProd); // ラジアン単位の角度
    }

    //ベクトルの線型補間
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




