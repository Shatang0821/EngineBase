#include "stdafx.h"
#include "World.h"
#include "Timer.h"

World mainWorld;

void World::Update(float DeltaTime)
{
	//レベルの更新
	currentLevel->Update(DeltaTime);

	//カメラの更新
	mainCamera->Calculate();

	//オブジェクトの更新
	for (auto& obj : GameObjects) {
		obj->Update(DeltaTime);
	}
	//削除予定のオブジェクトを削除する
	for (auto& obj : GameObjects_to_delete) {
		GameObjects.erase(obj);
	}
	//コンテナをクリア
	GameObjects_to_delete.clear();


	for (auto& obj : GameUIs) {

	}
	for (auto& obj : GameUIs_to_delete) {

	}
	GameUIs_to_delete.clear();

	for (auto& obj : GameTimers) {
		obj->Execute();
	}
}

void World::FixedUpdate()
{

}

void World::Render()
{

	for (auto& obj : GameRenderers) {
		obj->Render();
	}
}

void World::Input()
{
	mainController->PickInfo();
}
