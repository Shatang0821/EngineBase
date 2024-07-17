#include "stdafx.h"
#include "Camera.h"

float Camera::SmoothStep(float x)
{
	// x��1�����̏ꍇ�Ax��1�ɐݒ�
	x = x < 1 ? 1 : x;
	// x�ׂ̂�����v�Z���Ċ��炩�ȕ�Ԓl��Ԃ�
	return pow(x, float(smoothness) / 100);
}

void Camera::Update(float DeltaTime)
{
	static bool first = true;
	if (first) {
		transform_virtual.position = GetWorldPosition();
		transform_virtual.rotation = GetWorldRotation();
		springArmLength_virtual = springArmLength;
		first = false;
	}

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

	//���炩�Y�[��
	if (smoothnessForSpringArm) {
		springArmLength_virtual = Math::Lerp(springArmLength_virtual, springArmLength, 0.1f / smoothnessForSpringArm);
	}
	else springArmLength_virtual = springArmLength;

	if (shakeFlag)
	{
		if (GetLocalPosition() == shakeCenter)
		{
			shakeSpeed.x = float(Math::RandInt(-2, 2));
			shakeSpeed.y = float(Math::RandInt(-2, 2));
			shakeIntensity -= float(shakeDecay) / 100;

			if (shakeIntensity <= 0) {
				shakeFlag = false;

				return;
			}
		}

		if (Vector2::Distance(GetLocalPosition(), shakeCenter) < shakeIntensity) {
			AddPosition(shakeSpeed);
			transform_virtual.position += shakeSpeed;
		}
		else {
			shakeSpeed = shakeSpeed * -1;
			AddPosition(shakeSpeed);
			transform_virtual.position += shakeSpeed;
		}
	}
}

void Camera::SetMainCamera()
{
	// ���̃J���������C���J�����Ƃ��Đݒ�
	mainWorld.mainCamera = this;
}

void Camera::SetSmoothness(short smooth)
{
	// smooth�l��0����100�͈̔͂ɃN�����v���Đݒ�
	this->smoothness = Math::clamp(smooth, (short)0.0, (short)100.0);
}

void Camera::SetDistanceThreshold(float threshold)
{
	// �����������l��0.0����500.0�͈̔͂ɃN�����v���Đݒ�
	this->distanceThreshold = Math::clamp(threshold, 0.0f, 500.0f);
}

void Camera::SetSpringArmLength(float length)
{
	this->springArmLength = Math::clamp(length, 0.5f, 10000.f);
}

void Camera::SetSpringArmSmoothness(int smooth)
{
	this->smoothnessForSpringArm = Math::clamp(smooth, 0, 100);
}

void Camera::ShakeCamera(int intensity,int decay)
{
	intensity = Math::clamp(intensity, 0, 100);
	shakeIntensity = (float)intensity;
	shakeDecay = decay;
	if (!shakeFlag) shakeCenter = GetLocalPosition();
	shakeFlag = true; 
}

