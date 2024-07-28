#include "stdafx.h"
#include "GameLevel.h"
#include "myApp.h"
#include "Platform.h"

GameLevel::GameLevel()
{
    //buttle = GameStatics::CreateObject<StaticMesh>(Vector2(256,256));
    //buttle->GetComponentByClass<SpriteRenderer>()->LoadSprite(ResID::Tex_Bullet);

    //buttle->Destroy();
    player = GameStatics::CreateObject<Player>(Vector2(0, 0));
    GameStatics::CreateObject<Platform>(Vector2(0, 0));
    
    //Player‚ğ50ŒÂ¶¬‚µ‚Ä‚­‚¾‚³‚¢
    for (int i = 0; i < 50; i++)
    {
        float x = i % 5;
        float y = i / 5;
        GameStatics::CreateObject<Platform>(Vector2(x * 40, y * 40));
    }
    
    //player->Destroy();
}

void GameLevel::Update(float DeltaTime)
{
	//buttle->AddRotation(DeltaTime * 15);
	//buttle->AddPosition(DeltaTime * 60);
	//player->AddRotation(DeltaTime * 15);
}
