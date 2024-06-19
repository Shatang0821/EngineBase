/**
 * @file Object.h
 * @brief オブジェクトの基底クラスとなる
 *
 * このファイルには、ゲーム内すべてのオブジェクトの基底クラスが定義されています。
 *
 * @author サトウ
 * @date 2024/06/19
 */
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Base.h"
#include "SceneComponent.h"

/**
 * @class Object
 * @brief ゲームオブジェクトの基底クラス
 *
 * このクラスは、ゲーム内のオブジェクトを表し、複数のコンポーネントを保持します。
 */
class Object : public Base
{
	friend void Component::Destruct();
protected:
	//! オブジェクトのルートとなるシーンコンポーネントを指します
	SceneComponent* root = nullptr;
	//! オブジェクトに所属するコンポーネントを管理します。
	std::set<Component*>components;
	//! 削除予定のコンポーネントを管理します。
	std::set<Component*>components_to_destruct;
public:
	/**
	 * @brief コンポーネントの生成
	 *
	 * 指定された位置に新しいコンポーネントを生成し、オブジェクトに追加します。
	 *
	 * @tparam T 生成するコンポーネントの型
	 * @param pos コンポーネントの位置
	 * @return T* 生成されたコンポーネントへのポインタ
	 */
	template<typename T>
	T* ConstructComponent(Vector2 pos) {
		T* pCom = new T();
		//派生クラスを基底クラスにキャストするだけからstatic_castを使う
		if (Component* pBuffer = static_cast<Component*>(pCom)) {
			//pBuffer->SetPosition(pos);
			pBuffer->SetOwner(this);
			components.insert(pBuffer);
			return pCom;
		}
		//失敗したらnullを返す
		return nullptr;
	}
	/**
	 * @brief オブジェクトの更新処理
	 *
	 * この関数は、オブジェクトの状態を更新します。
	 *
	 * @param DeltaTime 前フレームからの経過時間
	 */
	virtual void Update(float DeltaTime) override;
};

#endif // !_OBJECT_H_



