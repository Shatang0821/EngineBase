/**
 * @file Controller.h
 * @brief ゲームシーンコントローラーを管理するクラス
 *
 * @author サトウ
 * @date 2024/06/30
 */

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Controller.h"
#include "Timer.h"

class GameController : public Controller
{
	Timer OverallTimeHandle;
	Timer ShakeTimeHandle;
public:
	GameController();

	virtual void SetUpInputComponent(InputComponent* inputComponent) override;

	void Update(float DeltaTime) override;

	void Shake(BYTE);
private:
	//! カメラのスプリングアームの長さ
	float armLength = 1;

	void ZoomIn(BYTE);
	void ZoomOut(BYTE);


};

#endif // !_GAMECONTROLLER_H_
