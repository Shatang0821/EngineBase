#include "stdafx.h"
#include "GameLevel.h"
#include "myApp.h"
GameLevel::GameLevel()
{
	buttle = GameStatics::CreateObject<StaticMesh>(Vector2(256,256));
	buttle->GetComponentByClass<SpriteRenderer>()->LoadSprite(ResID::Tex_Bullet);
}

void GameLevel::Update(float DeltaTime)
{
	//buttle->AddRotation(DeltaTime * 15);
	//buttle->AddPosition(DeltaTime * 60);
}
