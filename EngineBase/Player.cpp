#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

Player::Player()
{
	//���C���̐ݒ�
	auto spriteRenderer = GetComponentByClass<SpriteRenderer>();
	spriteRenderer->SetLayer(1);

	//�A�j���[�^�[�̐����Ɛݒ�
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
