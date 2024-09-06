#include "stdafx.h"
#include "GameLevel.h"
#include "../Engine/myApp.h"
#include "Platform.h"
#include "Block.h"
GameLevel::GameLevel()
{
    //buttle = GameStatics::CreateObject<StaticMesh>(Vector2(256,256));
    //buttle->GetComponentByClass<SpriteRenderer>()->LoadSprite(ResID::Tex_Bullet);

    //buttle->Destroy();
    player = GameStatics::CreateObject<Player>(Vector2(-100, -100));
    GameStatics::CreateObject<Platform>(Vector2(0, 100));
    /*for(int i = 0; i< 200; i++)
	{
		GameStatics::CreateObject<Block>(Vector2(i*2, -50));
	}*/
   /* for(int y = - HEIGHT / 2; y < HEIGHT / 2; y+=64)
	{
		for(int x = -WIDTH / 2; x < WIDTH / 2; x+=64)
		{
            GameStatics::CreateObject<Block>(Vector2(x, y));
		}
	}*/
    //GameStatics::CreateObject<Block>(Vector2(0, 100));
    //player->Destroy();
}

void GameLevel::Update(float DeltaTime)
{

}
