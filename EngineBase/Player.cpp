#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//レイヤの設定
	auto spriteRenderer = ConstructComponent<SpriteRenderer>();
	spriteRenderer->SetLayer(1);

	//アニメーターの生成と設定
	animator = ConstructComponent<Animator>();
	ani.Load(ResID::Tex_Player);
	ani.SetInterVal(0.02f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");
}
