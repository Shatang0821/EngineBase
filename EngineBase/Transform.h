/**
 * @file Transform.h
 * @brief 位置、回転、スケールを表す構造体となる
 *
 * このファイルには、変換情報が定義されています。
 *
 * @author サトウ
 * @date 2024/06/19
 */
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Vector2.h"

/**
 * @struct Transform
 * @brief 位置、回転、スケールを表す構造体
 *
 * この構造体は、オブジェクトの位置、回転、スケールを管理します。
 */
struct Transform
{
    Vector2 position;    /**< 位置 */
    float rotation;      /**< 回転(度数法) */
    Vector2 scale;       /**< スケール */

    /**
     * @brief デフォルトコンストラクタ
     *
     * 位置を(0, 0)、回転を0、スケールを(1, 1)に初期化します。
     */
    Transform() :position(0, 0), rotation(0), scale(1, 1) {}

    /**
    * @brief パラメータ付きコンストラクタ
    *
    * 指定された位置、回転、スケールで初期化します。
    *
    * @param pos 初期化する位置
    * @param rot 初期化する回転
    * @param scale 初期化するスケール
    */
    Transform(const Vector2& pos, float rot, const Vector2& scale)
        :position(pos), rotation(rot), scale(scale) {}

    /**
     * @brief 単位変換を返す関数
     *
     * 位置を(0, 0)、回転を0、スケールを(1, 1)に設定したTransformオブジェクトを返します。
     *
     * @return Transform 単位変換を表すTransformオブジェクト
     */
    Transform Identity() const {
        return Transform(Vector2::Zero(), 0, Vector2::One());
    }

    /**
	 * @brief ワールド座標をカメラ座標に変換する関数
	 *
	 * ワールド座標をカメラ座標に変換します。
	 *
	 * @param worldPos ワールド位置座標
	 * @return Vector2 カメラ座標
	 */
    static Vector2 WorldToCamera(const Vector2& worldPos);

    /**
     * @brief ワールド座標をビュー座標に変換する関数
     *
     * ワールド座標をビュー座標に変換します。
     *
     * @param worldPos ワールド位置座標
     * @return Vector2 ビュー座標
     */
    static Vector2 WordToScreen(const Vector2& worldPos);
};

#endif // !_TRANSFORM_H_

