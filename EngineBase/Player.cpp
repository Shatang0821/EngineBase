#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

Player::Player()
{
	//レイヤの設定
	auto spriteRenderer = GetComponentByClass<SpriteRenderer>();
	spriteRenderer->SetLayer(1);

	//アニメーターの生成と設定
	animator = ConstructComponent<Animator>();
	ani.Load(ResID::Tex_Player);
	ani.SetInterVal(0.02f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");
}

void Player::Update(float DeltaTime)
{
	StaticMesh::Update(DeltaTime);

	if (InputManager::Instance()->IsPushKey(DIK_W))
	{
		AddPosition(Vector2(0, -100) * DeltaTime);
	}
	if (InputManager::Instance()->IsPushKey(DIK_S))
	{
		AddPosition(Vector2(0, 100) * DeltaTime);
	}
	if (InputManager::Instance()->IsPushKey(DIK_A))
	{
		AddPosition(Vector2(-100, 0)* DeltaTime);
	}
	if (InputManager::Instance()->IsPushKey(DIK_D))
	{
		AddPosition(Vector2(100, 0) * DeltaTime);
	}
}
