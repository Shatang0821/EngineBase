#include "stdafx.h"
#include "World.h"
#include "Timer.h"
#include "InputManager.h"
#include "MyApp.h"
#include "Collider.h"

#include "../Project/GameLevel.h"
#include "../Project/GameController.h"
#include "Debug.h"

World mainWorld;

bool World::Init()
{
	//コントローラーの生成
	mainWorld.mainController = GameStatics::CreateObject<GameController>();
	//ワールド初期化
	mainWorld.currentLevel = new GameLevel;
	mainWorld.gameInstance = new GameInstance;


	return true;
}

void World::Update(float DeltaTime)
{
	//レベルの更新
	currentLevel->Update(DeltaTime);

	//オブジェクトの更新
	for (auto& obj : GameObjects) {
		if(obj != nullptr)
			obj->Update(DeltaTime);
	}
	//オブジェクトの追加
	for(auto& obj : GameObjects_to_add)
	{
		GameObjects.insert(obj);
		obj->BeginPlay();
	}
	GameObjects_to_add.clear();

	//削除予定のオブジェクトを削除する
	for (auto& obj : GameObjects_to_delete) {
		delete obj;
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

void World::FixedUpdate(float fixedDeltaTime)
{
	//物理更新
	for(auto& obj : GameObjects)
	{
		obj->FixedUpdate(fixedDeltaTime);
	}

	ProcessColliderZones();
	
}

void World::ProcessColliderZones()
{
	/*for (auto me : GameColliders) {
		for (auto he : GameColliders) {
			if (he != me) {
				me->Insert(he);
			}
		}
	}*/
	for (auto& arr_i : ColliderZones) {
		for (auto& arr_j : arr_i) {
			if (!arr_j.empty()) {
				for (auto& me : arr_j)
				{
					for (auto& he : arr_j)
						if (he != me) me->Insert(he);
				}
			}
		}
			
	}
		

	for(auto& it : GameColliders)
		it->Erase();
}

void World::Render()
{
	for (auto& obj : GameRenderers) {
		obj->Render();
	}

	Debug();
}

void World::Input()
{
	//mainController->PickInfo();
	InputManager::Instance()->UpdateInput(MyApp::Instance()->GetHWND());
}

void World::Debug()
{
	wchar_t text[50];
	swprintf(text, 50, L"%u", fps); // 数値を文字列に変換
	Debug::RenderText(MyApp::Instance()->GetDevice(), 0, 0,text);

	for(auto & obj : GameObjects)
	{
		obj->DrawDebug();
	}

	for (auto& obj : GameColliders) {
		obj->DrawDebugLine();
	}

}

void World::ReleaseData()
{
	//オブジェクトの解放
	for (auto obj : GameObjects) {
		obj->Destroy();

	}
	//コンテナをクリア
	GameObjects.clear();

	for (auto obj : GameObjects_to_delete) {
		delete obj;
	}
	GameObjects_to_delete.clear();

	//タイマーの解放
	for (auto obj : GameTimers) {
		delete obj;
	}
	GameTimers.clear();

	//削除予定のオブジェクトを削除する
	for (auto obj : GameObjects_to_delete) {
		delete obj;
	}
	GameObjects_to_delete.clear();
}

bool ColliderSort::operator()(const Collider* a, const Collider* b) const
{
	{
		if (a->GetLayer() == b->GetLayer())
			return a < b;
		else
			return a->GetLayer() < b->GetLayer();
	}
}
