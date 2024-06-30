#include "stdafx.h"
#include "Camera.h"

float Camera::SmoothStep(float x)
{
	// x��1�����̏ꍇ�Ax��1�ɐݒ�
	x = x < 1 ? 1 : x;
	// x�ׂ̂�����v�Z���Ċ��炩�ȕ�Ԓl��Ԃ�
	return pow(x, float(smoothness) / 100);
}

void Camera::SetMainCamera()
{
	// ���̃J���������C���J�����Ƃ��Đݒ�
	mainWorld.mainCamera = this;
}

void Camera::SetSmoothness(short smooth)
{
	// smooth�l��0����100�͈̔͂ɃN�����v���Đݒ�
	this->smoothness = std::clamp(smooth, (short)0.0, (short)100.0);
}

void Camera::SetDistanceThreshold(float threshold)
{
	// �����������l��0.0����500.0�͈̔͂ɃN�����v���Đݒ�
	this->distanceThreshold = std::clamp(threshold, 0.0f, 500.0f);
}

void Camera::Calculate()
{
	// ���炩�����ݒ肳��Ă���ꍇ
	if (smoothness) {
		// �J�����̌��݈ʒu�ƖڕW�ʒu�̋������v�Z���A�����������l�Ő��K��
		float distance = Vector2::Distance(transform_virtual.position, GetWorldPosition()) / distanceThreshold;
		// �X���[�X�X�e�b�v�֐����g�p���ĕ�Ԓl���v�Z
		float interpolationFactor = 0.1f / smoothness * SmoothStep(distance);
		// ���݈ʒu�ƖڕW�ʒu�̊Ԃ���`���
		transform_virtual.position = Vector2::Lerp(transform_virtual.position, GetWorldPosition(), interpolationFactor);
	}
	else {
		// ���炩����0�̏ꍇ�A���ږڕW�ʒu�ɐݒ�
		transform_virtual.position = GetWorldPosition();
	}

}
