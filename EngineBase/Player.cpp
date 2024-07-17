#include "stdafx.h"
#include "Player.h"

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
