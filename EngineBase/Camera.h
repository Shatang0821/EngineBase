/**
 * @file Camera.h
 * @brief カメラクラスの定義
 *
 * このファイルには、Cameraクラスが定義されています。
 * Cameraクラスは、シーン内のカメラの動きや設定を管理します。
 *
 * @date 2024/06/29
 * @autor サトウ
 */
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "World.h"
#include "SceneComponent.h"

 /**
  * @class Camera
  * @brief シーンコンポーネントとしてのカメラクラス
  *
  * このクラスは、シーン内のカメラの動きや設定を管理します。
  * カメラの位置、滑らかさ、距離しきい値などを設定し、カメラの動きを制御します。
  */
class Camera :public SceneComponent
{
	//! 変換情報のバッファ
	Transform transform_virtual;

	//! 距離しきい値 0.001~500
	float distanceThreshold = 10.0f;
	//! なめらかさ 0~100
	short smoothness = 30;

	/* カメラシェーク */

	//! カメラの揺れの強度 0~ 100
	float shakeIntensity = 0.f;
	//! カメラ揺れのフラグ
	bool shakeFlag = false;
	//! カメラ揺れの中心
	Vector2 shakeCenter = Vector2::Zero();
	//! カメラ揺れの速度
	Vector2 shakeSpeed = Vector2(0.05f, 0.05f);
	//! カメラ揺れの減衰値
	int shakeDecay = 5;

public:
	/* カメラズーム */
	
	//! ばねの長さ 1~10000
	float springArmLength = 1.0f;

	//! ばねの長さの仮想値
	float springArmLength_virtual = 5.0f;

	//! ばねの滑らかさ0~100
	float smoothnessForSpringArm = 1.0f;

	/**
	 * @brief SmoothStep関数
	 *
	 * この関数は、0.0から1.0の範囲内で滑らかな補間を行うための関数です。
	 * 入力値xが0.0未満の場合は0.0、1.0を超える場合は1.0にクランプされます。
	 *
	 * @param x 入力値（0.0から1.0の範囲）
	 * @return float 補間された値
	 */
	float SmoothStep(float x);
public:
	/**
	 * @brief カメラのロジック計算を行います
	 *
	 * この関数は、カメラの位置や動きを制御するための計算を行います。
	 */
	virtual void Update(float DeltaTime) override;
	/**
	 * @brief メインカメラの切り替え処理
	 *
	 * この関数は、自身をメインカメラに設定する。
	 */
	void SetMainCamera();
	/**
	 * @brief カメラの実際位置を取得します
	 *
	 * この関数は、カメラの現在の実際位置を返します。
	 * オブジェクトがNULLである場合、ゼロベクトルを返します。
	 *
	 * @return Vector2 カメラの現在位置。オブジェクトがNULLの場合はゼロベクトル。
	 */
	Vector2 GetCameraPosition() { 
		if (this == NULL)
		{
			return Vector2::Zero();
		}
		return transform_virtual.position; 
	}
	/**
	 * @brief カメラの滑らかさを設定します
	 *
	 * この関数は、カメラの動きを制御する滑らかさの値を設定します。
	 *
	 * @param smooth 設定する滑らかさの値（0〜100）
	 */
	void SetSmoothness(short smooth);
	/**
	 * @brief カメラの距離しきい値を設定します
	 *
	 * この関数は、カメラの動きを制御する距離しきい値を設定します。
	 *
	 * @param threshold 設定する距離しきい値（0〜500）
	 */
	void SetDistanceThreshold(float threshold);

	void SetSpringArmLength(float length);

	void SetSpringArmSmoothness(int smooth);

	void ShakeCamera(int intensity,int decay = 20);
};

#endif // !_CAMERA_H_

