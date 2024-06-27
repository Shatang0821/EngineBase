#include "World.h"
#include "Timer.h"

World mainWorld;

void World::Update(float DeltaTime)
{
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

void World::Render()
{
	for (auto& obj : GameRenderers) {

	}
}

void World::Input()
{
}
