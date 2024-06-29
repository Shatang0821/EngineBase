/**
 * @file StaticMesh.h
 * @brief 静的メッシュクラスの定義
 *
 * このファイルには、StaticMeshクラスが定義されています。
 * StaticMeshクラスは、静的なメッシュオブジェクトを表し、
 * スプライトレンダラーを使用して描画を行います。
 *
 * @date 2024/06/29
 * @author サトウ
 */
#ifndef _STATICMESH_H_
#define _STATICMESH_H_

#include "Object.h"
#include "SpriteRenderer.h"

 /**
  * @class StaticMesh
  * @brief 静的メッシュオブジェクトを表すクラス
  *
  * このクラスは、静的なメッシュオブジェクトを表し、
  * スプライトレンダラーを使用して描画を行います。
  * Objectクラスを基底クラスとし、メッシュの描画にSpriteRendererを使用します。
  */
class StaticMesh : public Object
{
private:
    //! スプライトを描画するためのレンダラー
	SpriteRenderer* renderer;
public:
    /**
     * @brief コンストラクタ
     *
     * StaticMeshクラスのインスタンスを初期化します。
     * スプライトレンダラーのインスタンスを作成し、初期化します。
     */
	StaticMesh();
};

#endif // !_STATICMESH_H_


