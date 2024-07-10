/**
 * @file Controller.h
 * @brief 入力コンポーネントを管理するクラス
 *
 * @author サトウ
 * @date 2024/06/30
 */
#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include "Component.h"

/**
 * @enum InputType
 * @brief 入力の種類を表す列挙型
 *
 * 入力が押された、離された、押し続けられた状態を表します。
 */
enum InputType
{
	Pressed,   ///< 入力が押された状態
	Released,  ///< 入力が離された状態
	Holding    ///< 入力が押し続けられた状態
};

/**
 * @struct KeyBindInfo
 * @brief キーバインド情報を保持する構造体
 *
 * 入力に対するコールバック関数と入力の種類、押されているかの状態を保持します。
 */
struct KeyBindInfo
{
	std::function<void()> func; ///< コールバック関数
	InputType type; ///< 入力の種類
	bool isPressed = false; ///< 入力が押されているかどうかの状態
};

/**
 * @class InputComponent
 * @brief 入力を管理するコンポーネントクラス
 *
 * このクラスは、入力のマッピングとバインディングを管理し、対応するアクションを実行します。
 * Componentクラスを基底クラスとして継承しています。
 */
class InputComponent : public Component
{
public:
	/**
	 * @brief 入力マッピングを設定する
	 *
	 * 入力名と値を対応付けて入力マッピングを設定します。
	 *
	 * @param mappingName マッピングする入力の名前
	 * @param code 入力キーの値
	 */
	void SetMapping(std::string mappingName, BYTE code);
	/**
	 * @brief アクションに対する入力バインディングを設定するテンプレート関数
	 *
	 * 指定したアクション名と入力タイプに対して、オブジェクトのメンバ関数をバインドします。
	 *
	 * @tparam T クラスの型
	 * @param actionName アクション名
	 * @param type 入力の種類
	 * @param obj オブジェクトのポインタ
	 * @param func バインドするメンバ関数
	 */
	template<typename T>
	void BindAction(std::string actionName, InputType type,T*obj,void(T::*func)()) {
		if (mappings.find(actionName) != mappings.end()) {
			callbacks.insert({ actionName,KeyBindInfo{std::bind(func,obj),type ,false} });
		}
	}
	/**
	 * @brief 入力の更新を行う
	 *
	 * フレームごとに入力の状態を更新し、対応するアクションを実行します。
	 *
	 * @param DeltaTime フレーム間の経過時間
	 */
	virtual void Update(float DeltaTime) override;
private:
	//! 入力マッピング
	std::map<std::string, BYTE>mappings;
	//! 入力に対するコールバック
	std::map<std::string, KeyBindInfo>callbacks;
};

#endif // !_INPUTCOMPONENT_H_


