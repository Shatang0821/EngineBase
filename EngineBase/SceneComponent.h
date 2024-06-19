/**
 * @file SceneComponent.h
 * @brief シーンコンポーネントの基底クラスとなる
 *
 * このファイルは、シーンコンポーネントの基底クラスを定義しています。
 *
 * @author サトウ
 * @date 2024/06/19
 */

#ifndef _SCENECOMPONENT_H_
#define _SCENECOMPONENT_H_

#include <set>
#include "Component.h"
#include "Transform.h"

 /**
  * @class SceneComponent
  * @brief シーン内のコンポーネントを表すクラス
  *
  * このクラスは、シーン内のコンポーネントを表し、親子関係を持つことができます。
  */
class SceneComponent : public Component
{
protected:
    //! コンポーネントの変換情報
    Transform transform;
    //! コンポーネントの子要素を管理します。頻繁に削除や追加が行われるため、setを使用しています。
    std::set<SceneComponent*>children;
    //! コンポーネントの親要素を指します。
    SceneComponent* parent = nullptr;
public:
    /**
     * @brief コンポーネントの更新処理
     *
     * この関数は、コンポーネントの状態を更新します。
     *
     * @param DeltaTime 前フレームからの経過時間
     */
    virtual void Update(float DeltaTime) override;

    /**
    * @brief 親コンポーネントの設定
    *
    * この関数は、コンポーネントの親要素を設定します。
    *
    * @param par 設定する親コンポーネントへのポインタ
    */
    void SetAttachment(SceneComponent* par);

    /**
     * @brief 削除処理をサポートする関数
     *
     * この関数は、コンポーネントの削除処理をサポートします。
     */
    void process_Destruct();

    /**
     * @brief コンポーネントの削除処理
     *
     * この関数は、コンポーネントの削除処理を行います。
     */
    virtual void Destruct() override;
};

#endif // !_SCENECOMPONENT_H_

