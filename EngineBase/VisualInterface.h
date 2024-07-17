/**
 * @file VisualInterface.h
 * @brief 視角インターフェース
 *
 * @author サトウ
 * @date 2024/06/28
 */
#ifndef _VISUALINTERFACE_H_
#define _VISUALINTERFACE_H_

#include "MyTexture.h"
#include "ResourceManager.h"

 /**
  * @class LayerInterface
  * @brief レイヤー管理のためのインターフェースクラス
  *
  * このクラスは、レイヤー情報を持ち、レイヤーの設定および取得を行うための
  * インターフェースを提供します。ゲームやグラフィックスのシステムで、
  * オブジェクトの描画順序や処理順序を管理するために使用されます。
  */
class LayerInterface
{
private:
	//！ レイヤーの値（デフォルトは0）
	int layer = 0;
public:
	/**
	 * @brief コンストラクタ
	 *
	 * LayerInterfaceクラスのインスタンスを初期化します。
	 * デフォルトではレイヤーの値は0に設定されます。
	 */
	LayerInterface();
	/**
	* @brief デストラクタ
	*
	* LayerInterfaceクラスのインスタンスを破棄します。
	* 派生クラスで適切にオーバーライドすることができます。
	*/
	virtual ~LayerInterface();
	/**
	 * @brief レイヤーを設定する
	 *
	 * レイヤーの値を設定します。レイヤーの値はオブジェクトの描画順序や
	 * 処理順序を決定するために使用されます。
	 *
	 * @param layer 設定するレイヤーの値
	 */
	void SetLayer(int layer);
	/**
	 * @brief レイヤーの値を取得する
	 *
	 * 現在設定されているレイヤーの値を返します。
	 *
	 * @return 現在のレイヤーの値
	 */
	int GetLayer() const;
	/**
	 * @brief 描画処理を行う純粋仮想関数
	 *
	 * この関数は、オブジェクトの描画処理を行います。
	 * 派生クラスで具体的な描画ロジックを実装する必要があります。
	 */
	virtual void Render() = 0;
};

/**
 * @class ImageInterface
 * @brief 画像インターフェースクラス
 *
 * このクラスは、画像（スプライト）の管理と透過度の設定および取得を行うための
 * インターフェースを提供します。描画に使用するテクスチャと透過度を管理します。
 */
class ImageInterface
{
public:
	//! テクスチャポインタ
	MyTexture* sprite = nullptr;
	struct SpriteInfo
	{
		POINT offset = { 0,0 };
	}spriteInfo;//補充情報

	//! 透明度
	float alpha = 1;

	float angle = 0;
public:
	/**
	 * @brief 透過度を取得する
	 *
	 * 現在の画像の透過度を返します。
	 *
	 * @return 透過度（0.0〜1.0の範囲）
	 */
	float GetTransprancy() { return alpha; }
	/**
	 * @brief 透過度を設定する
	 *
	 * 画像の透過度を設定します。透過度は0.0が完全透明、1.0が完全不透明を表します。
	 *
	 * @param transprancy 設定する透過度（0.0〜1.0の範囲）
	 */
	void SetTransprancy(float transprancy) { alpha = transprancy; }
	/**
	 * @brief 画像の取得
	 *
	 * リソースマネージャーから画像を取得する
	 *
	 * @param id 素材id
	 */
	void LoadSprite(ResID id);
};

#endif // !_VISUALINTERFACE_H_

