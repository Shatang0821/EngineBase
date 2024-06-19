/**
 * @file Vector2.h
 * @brief 2Dベクトルを表す構造体となる
 *
 * このファイルには、2Dベクトルが定義されています。
 *
 * @author サトウ
 * @date 2024/06/19
 */
#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <iostream>

/**
 * @struct Vector2
 * @brief 2Dベクトルを表す構造体
 *
 * この構造体は、2Dベクトルの基本的な操作を提供します。
 */
struct Vector2
{

    //! X座標
    float x;
    //! Y座標
    float y;

    /**
      * @brief デフォルトコンストラクタ
      *
      * X座標とY座標を指定された値で初期化します。
      *
      * @param x X座標
      * @param y Y座標
      */
    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    /**
     * @brief ベクトルの加算
     *
     * 2つのベクトルを加算します。
     *
     * @param v 加算するベクトル
     * @return Vector2 加算結果
     */
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    /**
     * @brief ベクトルの加算と代入
     *
     * ベクトルを加算し、その結果を代入します。
     *
     * @param v 加算するベクトル
     * @return Vector2& 加算結果
     */
    Vector2& operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    /**
     * @brief ベクトルの減算
     *
     * 2つのベクトルを減算します。
     *
     * @param v 減算するベクトル
     * @return Vector2 減算結果
     */
    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    /**
     * @brief ベクトルの減算と代入
     *
     * ベクトルを減算し、その結果を代入します。
     *
     * @param v 減算するベクトル
     * @return Vector2& 減算結果
     */
    Vector2& operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    /**
     * @brief ベクトルの乗算
     *
     * 2つのベクトルを乗算します。
     *
     * @param v 乗算するベクトル
     * @return Vector2 乗算結果
     */
    Vector2 operator*(const Vector2& v) const {
        return Vector2(x * v.x, y * v.y);
    }

    /**
     * @brief ベクトルの乗算と代入
     *
     * ベクトルを乗算し、その結果を代入します。
     *
     * @param v 乗算するベクトル
     * @return Vector2& 乗算結果
     */
    Vector2& operator*=(const Vector2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    /**
     * @brief スカラー乗算
     *
     * ベクトルにスカラーを乗算します。
     *
     * @param scalar 乗算するスカラー値
     * @return Vector2 乗算結果
     */
    Vector2 operator*(const float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    /**
     * @brief スカラー乗算と代入
     *
     * ベクトルにスカラーを乗算し、その結果を代入します。
     *
     * @param scalar 乗算するスカラー値
     * @return Vector2& 乗算結果
     */
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    /**
     * @brief ベクトルの大きさ（長さ）を計算します。
     *
     * @return float ベクトルの大きさ
     */
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    /**
     * @brief ベクトルを正規化します
     *
     * @return Vector2 正規化されたベクトル
     */
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag == 0) return Vector2(0, 0);
        return Vector2(x / mag, y / mag);
    }

    /**
     * @brief ベクトルの内積を計算します
     *
     * @param v 内積を計算するベクトル
     * @return float 内積
     */
    float dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    /**
     * @brief 2つのベクトル間の距離を計算します
     *
     * @param v 距離を計算するベクトル
     * @return float 距離
     */
    float distance(const Vector2& v) const {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }

    /**
     * @brief 2つのベクトルの間の角度を計算します
     *
     * @param v 角度を計算するベクトル
     * @return float ラジアン単位の角度
     */
    float angleBetween(const Vector2& v) const {
        float dotProd = dot(v);
        float magProd = magnitude() * v.magnitude();
        return std::acos(dotProd / magProd); // ラジアン単位の角度
    }

    /**
     * @brief ベクトルの線型補間を計算します
     *
     * @param v 補間するベクトル
     * @param t 補間係数（0から1の範囲）
     * @return Vector2 線型補間されたベクトル
     */
    Vector2 lerp(const Vector2& v, float t) const {
        return *this + (v - *this) * t;
    }

    /**
     * @brief ゼロベクトルを返す静的メソッド
     *
     * @return Vector2 (0.0f, 0.0f) のベクトル
     */
    static Vector2 Zero() {
        return Vector2(0.0f, 0.0f);
    }

    /**
     * @brief 単位ベクトルを返す静的メソッド
     *
     * @return Vector2 (1.0f, 1.0f) のベクトル
     */
    static Vector2 One() {
        return Vector2(1.0f, 1.0f);
    }
};

/**
 * @brief ベクトルを標準出力するオーバーロード演算子
 *
 * @param out 出力ストリーム
 * @param vec 出力するベクトル
 * @return std::ostream& 出力ストリーム
 */
static std::ostream& operator<<(std::ostream& out, const Vector2& vec)
{
    std::cout << "(" << vec.x << "," << vec.y << ")";
    return out;
}
#endif // !_VECTOR2_H_




