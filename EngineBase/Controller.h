#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"

class Controller :public Object
{
protected:
	class Camera* camera;
public:
	Controller();

	/**
	 * @brief ゲームプレイの開始時に呼び出されるメソッド
	 *
	 * この関数は、ゲームプレイが開始されるときに初期化処理を行うために呼び出されます。
	 * 親クラスの `BeginPlay` メソッドをオーバーライドして、カメラの初期化処理を実装します。
	 */
	virtual void BeginPlay() override;

	//入力処理
	void PickInfo(){}
};

#endif // !_CONTROLLER_H_

