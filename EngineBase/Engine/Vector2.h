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
#include <algorithm>
#include "Math.h"
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
	 * @brief ベクトルの除算
	 *
	 * 2つのベクトルを除算します。
	 *
	 * @param v 除算するベクトル
	 * @return Vector2 除算結果
	 */
    Vector2 operator/(const Vector2& v) const {
		return Vector2(x / v.x, y / v.y);
	}

    
    /**
	 * @brief ベクトルの除算と代入
	 *
	 * ベクトルを除算し、その結果を代入します。
	 *
	 * @param v 除算するベクトル
	 * @return Vector2& 除算結果
	 */
    Vector2& operator/=(const Vector2& v) {
    		x /= v.x;
            y /= v.y;
            return *this;
    }

    /**
     * @brief スカラー除算
     *
     * ベクトルにスカラーを除算します。
     *
     * @param scalar 除算するスカラー値
     * @return Vector2 除算結果
     */
    Vector2 operator/(const float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }


    Vector2 operator-() const
    {
        return Vector2(-x, -y);
    }

    
    /**
     * @brief ベクトルの大きさ（長さ）を計算します。
     *
     * @return float ベクトルの大きさ
     */
    float Length() const {
        return std::sqrt(x * x + y * y);
    }

    /**
     * @brief ベクトルを正規化します
     *
     * @return Vector2 正規化されたベクトル
     */
    Vector2 normalized() const {
        float mag = Length();
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
	 * @brief ベクトルの外積を計算します
	 *
	 * @param v 外積を計算するベクトル
	 * @return float 外積
	 */
    float cross(const Vector2& v) const {
		return x * v.y - y * v.x;
	}

    /**
     * @brief ベクトルの射影を計算します
     *
     * この静的メソッドは、ベクトルuをベクトルvに射影します。
     * 射影されたベクトルを返します。
     *
     * @param u 射影するベクトル
     * @param v 射影の基準となるベクトル
     * @return Vector2 射影されたベクトル
     */
    static Vector2 ProjectVector(const Vector2& u, const Vector2& v) {
		float scalar = Dot(u,v) / v.Length();
        return v.normalized() * scalar;
	}

    
    static float Dot(const Vector2& u, const Vector2& v) {
		return u.x * v.x + u.y * v.y;
	}

    /**
     * @brief 2つのベクトル間の距離を計算します
     *
     * この関数は、2つのベクトルstartとendの間のユークリッド距離を計算します。
     *
     * @param start 距離を計算する開始ベクトル
     * @param end 距離を計算する終了ベクトル
     * @return float 2つのベクトル間の距離
     */
    static float Distance(const Vector2& start, const Vector2& end) {
        return std::sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));
    }

    /**
     * @brief 2つのベクトルの間の角度を計算します
     *
     * @param v 角度を計算するベクトル
     * @return float ラジアン単位の角度
     */
    float angleBetween(const Vector2& v) const {
        float dotProd = dot(v);
        float magProd = Length() * v.Length();
        return std::acos(dotProd / magProd); // ラジアン単位の角度
    }

    /**
     * @brief 2つのベクトル間の線形補間を計算します
     *
     * この関数は、開始ベクトルと終了ベクトルの間を補間係数`t`に基づいて線形補間します。
     *
     * @param start 補間の開始ベクトル
     * @param end 補間の終了ベクトル
     * @param t 補間係数（0から1の範囲）
     * @return Vector2 線形補間されたベクトル
     */
    static Vector2 Lerp(const Vector2& start,const Vector2& end, float t) {
        t = Math::clamp(t, 0.001f, 0.1f);
        return start + (end - start) * t;
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

    /**
     * @brief ベクトルの等値比較
     *
     * 2つのベクトルが等しいかを比較します。
     *
     * @param v 比較するベクトル
     * @return bool 等しい場合はtrue、それ以外はfalse
     */
    bool operator==(const Vector2& v) const {
        return x == v.x && y == v.y;
    }

    /**
     * @brief ベクトルの非等値比較
     *
     * 2つのベクトルが等しくないかを比較します。
     *
     * @param v 比較するベクトル
     * @return bool 等しくない場合はtrue、それ以外はfalse
     */
    bool operator!=(const Vector2& v) const {
        return !(*this == v);
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




