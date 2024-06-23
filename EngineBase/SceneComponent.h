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
private:

    /**
     * @brief 削除処理をサポートする関数
     *
     * この関数は、コンポーネントの削除処理をサポートします。
     */
    void process_Destruct();

protected:
    //! コンポーネントの変換情報
    Transform transform;

    //! コンポーネントの子要素を管理します。頻繁に削除や追加が行われるため、setを使用しています。
    std::set<SceneComponent*>children;

    //! コンポーネントの親要素を指します。削除追加しやすいため
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
    * @brief 親コンポーネントの設定する関数
    *
    * この関数は、コンポーネントの親要素を設定します。
    *
    * @param par 設定する親コンポーネントへのポインタ
    */
    void AttachTo(SceneComponent* par);
    /**
    * @brief 親コンポーネントの設定する関数
    *
    * この関数は、コンポーネントの親要素を解除します。
    *
    * @param par 設定する親コンポーネントへのポインタ
    */
    void DetachFrom(SceneComponent* par);

    
    /**
     * @brief コンポーネントの削除処理する関数
     *
     * この関数は、コンポーネントの削除処理を行います。
     */
    virtual void Destruct() override;


    /**
     * @brief ローカル位置情報を取得する関数
     *
     * @return Vector2 ローカル位置
     */
    Vector2 GetLocalPosition() const { return transform.position; }
    /**
     * @brief 回転情報を取得する関数
     *
     * @return float 回転(度数法)
     */
    float GetLocalRotation() const { return transform.rotation; }
    /**
     * @brief スケール情報を取得する関数
     *
     * @return Vector2 スケール
     */
    Vector2 GetLocalScale() const { return transform.scale; }
    /**
     * @brief ワールド位置情報を取得する関数
     *
     * @return Vector2 ワールド位置(絶対位置)
     */
    Vector2 GetWorldPosition() const;
    /**
     * @brief ワールド回転情報を取得する関数
     *
     * @return float ワールド回転(度数法)
     */
    float GetWorldRotation() const;
    /**
     * @brief ワールドスケール情報を取得する関数
     *
     * @return Vector2 ワールドスケール
     */
    Vector2 GetWorldScale() const;
	/**
     * @brief ローカル位置を設定する関数
     * @param[in] pos 位置情報
    */
    void SetLocalPosition(const Vector2& pos) { transform.position = pos; }
    /**
     * @brief ローカル回転を設定する関数
     * @param[in] rot 回転情報
    */
    void SetLocalRotation(float rot) { transform.rotation = rot; }
    /**
     * @brief ローカルスケールを設定する関数
     * @param[in] scale スケール情報
    */
    void SetLocalScale(const Vector2& scale) { transform.scale = scale; }
    /**
     * @brief ローカル位置を加算する関数
     * @param[in] pos 位置情報
    */
    void AddPosition(const Vector2& pos) { transform.position += pos; }
    /**
     * @brief ローカル回転を加算する関数
     * @param[in] rot 回転情報
    */
    void AddRotation(float rot) { transform.rotation += rot; }
};

#endif // !_SCENECOMPONENT_H_

