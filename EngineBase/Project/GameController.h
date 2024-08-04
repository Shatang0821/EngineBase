/**
 * @file Controller.h
 * @brief ゲームシーンコントローラーを管理するクラス
 *
 * @author サトウ
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

	//ゲーム入力
	Vector2 axis;

	// キーの状態フラグ
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
	//! カメラのスプリングアームの長さ
	float armLength = 1;

	void ZoomIn(BYTE);
	void ZoomOut(BYTE);
	void CameraMove(BYTE);

	void SetAxis(BYTE);
	void ResetAxis(BYTE);

	void UpdateAxis();
};

#endif // !_GAMECONTROLLER_H_
