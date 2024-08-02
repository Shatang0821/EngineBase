#include "stdafx.h"
#include "GameLevel.h"
#include "myApp.h"
#include "Platform.h"
#include "Block.h"
GameLevel::GameLevel()
{
    //buttle = GameStatics::CreateObject<StaticMesh>(Vector2(256,256));
    //buttle->GetComponentByClass<SpriteRenderer>()->LoadSprite(ResID::Tex_Bullet);

    //buttle->Destroy();
    player = GameStatics::CreateObject<Player>(Vector2(0, -100));
    GameStatics::CreateObject<Platform>(Vector2(0, 100));
    
    for(int y = 0; y < HEIGHT / 2; y+=32)
	{
		for(int x = 0; x < WIDTH / 2; x+=32)
		{
            GameStatics::CreateObject<Block>(Vector2(x, y));
		}
	}
    //GameStatics::CreateObject<Block>(Vector2(0, 100));
    //player->Destroy();
}

void GameLevel::Update(float DeltaTime)
{
	//buttle->AddRotation(DeltaTime * 15);
	//buttle->AddPosition(DeltaTime * 60);
	//player->AddRotation(DeltaTime * 15);
}
