#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

/**
 * @brief Player�̃R���X�g���N�^�B
 *
 * �v���C���[�̏����ݒ���s���܂��B
 */
Player::Player()
{
	// ���C���[�̐ݒ�
	auto spriteRenderer = GetComponentByClass<SpriteRenderer>();
	spriteRenderer->SetLayer(1);

	// �A�j���[�^�[�̐����Ɛݒ�
	animator = ConstructComponent<Animator>();
	ani.Load(ResID::Tex_Player);
	ani.SetInterVal(0.02f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");

	// �{�b�N�X�R���C�_�[�̐ݒ�
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(32, 32));

	// �T�[�N���R���C�_�[�̐ݒ�
	circleCollider = ConstructComponent<CircleCollider>();
	circleCollider->AttachTo(root);
	circleCollider->SetRadius(16);
}

/**
 * @brief �v���C���[�̍X�V�����B
 *
 * �L�[���͂ɉ����ăv���C���[���ړ������܂��B
 * @param DeltaTime �O�t���[������̌o�ߎ���
 */
void Player::Update(float DeltaTime)
{
	StaticMesh::Update(DeltaTime);

	// W�L�[�ŏ�Ɉړ�
	if (InputManager::Instance()->IsPushKey(DIK_W))
	{
		AddPosition(Vector2(0, -100) * DeltaTime);
	}
	// S�L�[�ŉ��Ɉړ�
	if (InputManager::Instance()->IsPushKey(DIK_S))
	{
		AddPosition(Vector2(0, 100) * DeltaTime);
	}
	// A�L�[�ō��Ɉړ�
	if (InputManager::Instance()->IsPushKey(DIK_A))
	{
		AddPosition(Vector2(-100, 0) * DeltaTime);
	}
	// D�L�[�ŉE�Ɉړ�
	if (InputManager::Instance()->IsPushKey(DIK_D))
	{
		AddPosition(Vector2(100, 0) * DeltaTime);
	}
}
