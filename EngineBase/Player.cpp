#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	animator = ConstructComponent<Animator>();
	ani.Load(ResID::Tex_Player);
	ani.SetInterVal(0.02f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");
}
