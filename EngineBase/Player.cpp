#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

/**
 * @brief Playerのコンストラクタ。
 *
 * プレイヤーの初期設定を行います。
 */
Player::Player()
{
	// レイヤーの設定
	auto spriteRenderer = GetComponentByClass<SpriteRenderer>();
	spriteRenderer->SetLayer(1);

	// アニメーターの生成と設定
	animator = ConstructComponent<Animator>();
	ani.Load(ResID::Tex_Player);
	ani.SetInterVal(0.02f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");

	// ボックスコライダーの設定
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(32, 32));

	// サークルコライダーの設定
	circleCollider = ConstructComponent<CircleCollider>();
	circleCollider->AttachTo(root);
	circleCollider->SetRadius(16);
}

/**
 * @brief プレイヤーの更新処理。
 *
 * キー入力に応じてプレイヤーを移動させます。
 * @param DeltaTime 前フレームからの経過時間
 */
void Player::Update(float DeltaTime)
{
	StaticMesh::Update(DeltaTime);

	// Wキーで上に移動
	if (InputManager::Instance()->IsPushKey(DIK_W))
	{
		AddPosition(Vector2(0, -100) * DeltaTime);
	}
	// Sキーで下に移動
	if (InputManager::Instance()->IsPushKey(DIK_S))
	{
		AddPosition(Vector2(0, 100) * DeltaTime);
	}
	// Aキーで左に移動
	if (InputManager::Instance()->IsPushKey(DIK_A))
	{
		AddPosition(Vector2(-100, 0) * DeltaTime);
	}
	// Dキーで右に移動
	if (InputManager::Instance()->IsPushKey(DIK_D))
	{
		AddPosition(Vector2(100, 0) * DeltaTime);
	}
}
