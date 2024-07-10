/**
 * @file Controller.h
 * @brief コントローラーを管理するクラス
 *
 * @author サトウ
 * @date 2024/06/30
 */
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"
#include "InputComponent.h"

 /**
  * @class Controller
  * @brief ゲームオブジェクトのコントローラークラス
  *
  * このクラスは、ゲームオブジェクトの入力処理やカメラ操作を管理します。
  * Objectクラスを基底クラスとして継承しています。
  */
class Controller :public Object
{
private:
	//! 入力コンポーネント
	InputComponent* inputComponent;
protected:
	//! カメラオブジェクト
	class Camera* camera;

	/**
	 * @brief 入力コンポーネントの設定を行う純粋仮想関数
	 *
	 * この関数は、派生クラスで入力コンポーネントの設定を行うために実装されます。
	 */
	virtual void SetUpInputComponent(InputComponent* inputComponent) { ; }
public:
	/**
	 * @brief コンストラクタ
	 *
	 * Controllerクラスのインスタンスを初期化します。
	 */
	Controller();

	/**
	 * @brief ゲームプレイの開始時に呼び出されるメソッド
	 *
	 * この関数は、ゲームプレイが開始されるときに初期化処理を行うために呼び出されます。
	 * 親クラスの `BeginPlay` メソッドをオーバーライドして、カメラの初期化処理を実装します。
	 */
	virtual void BeginPlay() override;

	// 入力処理

};

#endif // !_CONTROLLER_H_

