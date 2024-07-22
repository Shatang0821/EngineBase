#include "stdafx.h"
#include "GameLevel.h"
#include "myApp.h"

GameLevel::GameLevel()
{
	//buttle = GameStatics::CreateObject<StaticMesh>(Vector2(256,256));
	//buttle->GetComponentByClass<SpriteRenderer>()->LoadSprite(ResID::Tex_Bullet);

	//buttle->Destroy();
	player = GameStatics::CreateObject<Player>(Vector2(0, 0));

	
	//player->Destroy();
}

void GameLevel::Update(float DeltaTime)
{
	//buttle->AddRotation(DeltaTime * 15);
	//buttle->AddPosition(DeltaTime * 60);
	//player->AddRotation(DeltaTime * 15);
}
