#include "stdafx.h"
#include "Camera.h"

float Camera::SmoothStep(float x)
{
	// xが1未満の場合、xを1に設定
	x = x < 1 ? 1 : x;
	// xのべき乗を計算して滑らかな補間値を返す
	return pow(x, float(smoothness) / 100);
}

void Camera::SetMainCamera()
{
	// このカメラをメインカメラとして設定
	mainWorld.mainCamera = this;
}

void Camera::SetSmoothness(short smooth)
{
	// smooth値を0から100の範囲にクランプして設定
	this->smoothness = std::clamp(smooth, (short)0.0, (short)100.0);
}

void Camera::SetDistanceThreshold(float threshold)
{
	// 距離しきい値を0.0から500.0の範囲にクランプして設定
	this->distanceThreshold = std::clamp(threshold, 0.0f, 500.0f);
}

void Camera::Calculate()
{
	// 滑らかさが設定されている場合
	if (smoothness) {
		// カメラの現在位置と目標位置の距離を計算し、距離しきい値で正規化
		float distance = Vector2::Distance(transform_virtual.position, GetWorldPosition()) / distanceThreshold;
		// スムースステップ関数を使用して補間値を計算
		float interpolationFactor = 0.1f / smoothness * SmoothStep(distance);
		// 現在位置と目標位置の間を線形補間
		transform_virtual.position = Vector2::Lerp(transform_virtual.position, GetWorldPosition(), interpolationFactor);
	}
	else {
		// 滑らかさが0の場合、直接目標位置に設定
		transform_virtual.position = GetWorldPosition();
	}

}
