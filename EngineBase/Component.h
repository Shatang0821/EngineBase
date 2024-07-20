/**
 * @file Component.h
 * @brief コンポーネントの基底クラスとなる
 *
 * このファイルは、すべてのコンポーネントの基底クラスを定義しています。
 *
 * @author サトウ
 * @date 2024/06/19
 */
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Base.h"

 /**
  * @class Component
  * @brief コンポーネントの基底クラス
  *
  * このクラスは、すべてのコンポーネントの基底クラスとなります。
  */
class Component : public Base
{
    friend class Object;
protected:
    //! コンポーネントの所有者（親オブジェクト）を指します。
    Object* pOwner = nullptr;
    
public:
    /**
      * @brief コンポーネントの更新処理
      *
      * この関数は、コンポーネントの状態を更新します。
      *
      * @param DeltaTime 前フレームからの経過時間
      */
    virtual void Update(float deltaTime) override;

    /**
	 * @brief 物理演算更新処理
	 *
	 * この関数は、コンポーネントの物理演算を更新します。
	 *
	 * @param fixedDeltaTime 固定フレーム時間
	 */
    virtual void FixedUpdate(float fixedeltaTime) {};
    /**
     * @brief 削除処理
     *
     * この関数は、コンポーネントの削除処理を行います。
     */
    virtual void Destruct();

    /**
     * @brief 所有者の設定
     *
     * この関数は、コンポーネントの所有者（親オブジェクト）を設定します。
     *
     * @param owner 設定する所有者へのポインタ
     */
    void SetOwner(class Object* owner) { pOwner = owner; }
};

#endif // !_COMPONENT_H_
