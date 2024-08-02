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
private:
    bool flipX = false; ///< X軸方向に反転するかどうか
    bool flipY = false; ///< Y軸方向に反転するかどうか
public:
    virtual ~SpriteRenderer() {};
    /**
     * @brief スプライトを描画する
     *
     * このメソッドは、LayerInterfaceから継承されたRenderメソッドをオーバーライドし、
     * スプライトの描画処理を実装します。
     */
	virtual void Render() override;

    /**
	 * @brief X軸方向に反転するかどうかを取得する
	 * @return X軸方向に反転するかどうか
	 */
    void SetFlipX(bool flip) { flipX = flip; }
    /**
     * @brief Y軸方向に反転するかどうかを取得する
     * @return Y軸方向に反転するかどうか
     */
    void SetFlipY(bool flip) { flipY = flip; }
};

#endif // !_SPRITERENDERER_H_



