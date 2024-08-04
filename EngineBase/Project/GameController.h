/**
 * @file Controller.h
 * @brief �Q�[���V�[���R���g���[���[���Ǘ�����N���X
 *
 * @author �T�g�E
 * @date 2024/06/30
 */

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "../Engine/Controller.h"
#include "../Engine/Timer.h"

class GameController : public Controller
{
private:
	Timer OverallTimeHandle;
	Timer ShakeTimeHandle;

	//�Q�[������
	Vector2 axis;

	// �L�[�̏�ԃt���O
	bool isWPressed = false;
	bool isSPressed = false;
	bool isAPressed = false;
	bool isDPressed = false;
public:
	GameController();

	virtual void SetUpInputComponent(InputComponent* inputComponent) override;

	void Update(float DeltaTime) override;

	void Shake(BYTE);

	Vector2 GetAxis() { return axis; }
private:
	//! �J�����̃X�v�����O�A�[���̒���
	float armLength = 1;

	void ZoomIn(BYTE);
	void ZoomOut(BYTE);
	void CameraMove(BYTE);

	void SetAxis(BYTE);
	void ResetAxis(BYTE);

	void UpdateAxis();
};

#endif // !_GAMECONTROLLER_H_
