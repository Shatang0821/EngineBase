/**
 * @file Animator.h
 * @brief アニメータークラスの定義
 *
 * このファイルには、Animator,Animationクラスが定義されています。
 * Animatorクラスは、アニメーションの再生や管理を行います。
 *
 * @date 2024/07/10
 * @autor サトウ
 */

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "myApp.h"
#include "Component.h"
#include "Timer.h"
#include "SpriteRenderer.h"
/**
 * @class Animation
 * @brief アニメーションクラス
 *
 * このクラスは、アニメーションの再生や管理を行います。
 * アニメーションのフレームレートやインデックスを管理し、
 * アニメーションの再生を制御します。
 */
class Animation 
{
	friend class Animator;
private:
	//! アニメーションのフレームレート
	int num = 0;
	//! アニメーションのオフセット
	POINT offset = { 0,0 };
	//! アニメーションのインデックス
	int index = 0;
	//! アニメーションの配列
	std::vector<MyTexture*> textures;
	//! 時計
	Timer clock;

public:
	Animation() {  }

	/**
	 * @brief アニメーションの更新設定
	 * 
	 * @param loop ループするかどうか
	 */
	void Bind(bool loop = true);

	void Load(ResID id, POINT delta = {0,0});

	/**
	 * @brief アニメーションの更新間隔を設定します
	 */
	void SetInterVal(double interval){ clock.SetDelay(interval); }

	/**
	 * @brief アニメーションのインデックスを設定します
	 */
	void SetIndex(int i) { index = i; }
};

/**
 * @class Animator
 * @brief アニメータークラス
 *
 * このクラスは、アニメーションの再生や管理を行います。
 * アニメーションの再生を制御し、アニメーションの切り替えを行います。
 */
class Animator final : public Component
{
private:
	//! アニメーションの配列
	std::unordered_map<std::string, Animation&> animations;

	//! 現在再生中のアニメーション
	Animation* aniNode = nullptr;

	//! レンダラー
	class SpriteRenderer* rendererAttached = nullptr;

public:
	virtual void Update(float DeltaTime) override;

	/**
	 * @brief アニメーションの登録
	 *
	 * 指定されたアニメーションを登録します。
	 *
	 * @param name アニメーションの名前
	 * @param ani 登録するアニメーション
	 */
	void Insert(std::string name,Animation& ani);


	Animation* GetNode()const {return aniNode; }

	/**
	 * @brief アニメーションの切り替え
	 *
	 * 指定されたアニメーションに切り替えます。
	 *
	 * @param nodeName 切り替えるアニメーションの名前
	 */
	void SetNode(std::string nodeName);

	void SetCalled(bool called);
};

#endif // !_ANIMATOR_H_

