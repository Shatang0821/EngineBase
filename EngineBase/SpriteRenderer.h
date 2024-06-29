/**
 * @file SpriteRenderer.h
 * @brief スプライトレンダラークラスの定義
 *
 * このファイルには、スプライトを描画するためのSpriteRendererクラスが定義されています。
 * SpriteRendererクラスは、シーンコンポーネント、レイヤーインターフェース、画像インターフェースを
 * 継承しており、これらの機能を統合してスプライトの描画を行います。
 *
 * @date 2024/06/29
 * @autor サトウ
 */
#ifndef _SPRITERENDERER_H_
#define _SPRITERENDERER_H_

#include "SceneComponent.h"
#include "VisualInterface.h"

 /**
  * @class SpriteRenderer
  * @brief スプライトを描画するためのクラス
  *
  * このクラスは、シーンコンポーネント、レイヤーインターフェース、画像インターフェースを
  * 継承し、スプライトの描画機能を提供します。最終クラス（final）として宣言されており、
  * 派生クラスを作成することはできません。
  */
class SpriteRenderer final: public SceneComponent,public LayerInterface,public ImageInterface
{
public:
    /**
     * @brief スプライトを描画する
     *
     * このメソッドは、LayerInterfaceから継承されたRenderメソッドをオーバーライドし、
     * スプライトの描画処理を実装します。
     */
	virtual void Render() override;
};

#endif // !_SPRITERENDERER_H_



