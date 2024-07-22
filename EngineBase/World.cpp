#include "stdafx.h"
#include "World.h"
#include "Timer.h"
#include "InputManager.h"
#include "MyApp.h"
#include "Collider.h"

#include "GameLevel.h"
#include "GameController.h"
#include "Debug.h"

World mainWorld;

bool World::Init()
{
	//ワールド初期化
	mainWorld.currentLevel = new GameLevel;
	mainWorld.gameInstance = new GameInstance;

	//mainWorld.mainController = new Controller;
	mainWorld.mainController = GameStatics::CreateObject<GameController>();

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
	//レベルの物理更新
	for (auto& arr_i : ColliderZones)
		for (auto& arr_j : arr_i)
			arr_j.clear();

	for(auto it = GameColliders.begin(); it != GameColliders.end(); ++it)
	{
		//前フレームの衝突情報をクリア
		(*it)->Clear();

		//コライダー半分情報を取得
		Vector2 half;
		if((*it)->GetShape() == Collider::COLLIDER_SHAPE_CIRCLE)
		{
			float r = Cast<CircleCollider>(*it)->GetRadius();
			half = Vector2(r, r);
		}
		else if((*it)->GetShape() == Collider::COLLIDER_SHAPE_BOX)
		{
			half = Cast<BoxCollider>(*it)->GetSize() / 2;
		}

		//左上の座標を取得
		Vector2 pos = (*it)->GetWorldPosition();
		pos -= half;

		int x = int(pos.x) / 100; x = Math::clamp(x, 0, 7);
		int y = int(pos.y) / 100; y = Math::clamp(y, 0, 5);

		//右下の座標を取得
		pos += half * 2;
		int x_1 = int(pos.x) / 100; x_1 = Math::clamp(x_1, 0, 7);
		int y_1 = int(pos.y) / 100; y_1 = Math::clamp(y_1, 0, 5);

		for(int i = x; i <= x_1; ++i)
		{
			for(int j = y; j <= y_1; ++j)
			{
				ColliderZones[i][j].insert(*it);
			}
		}
	}

	//コライダーの物理更新
	for (auto& arr_i : ColliderZones) {
		for (auto& arr_j : arr_i)
		{
			if (!arr_j.empty())
			{
				for (auto me = arr_j.begin(); me != arr_j.end(); ++me)
				{
					//自分以外のコライダーと判定
					for (auto other = arr_j.begin(); other != arr_j.end(); ++other)
					{
						if (other != me) {
							//衝突判定
							(*me)->Inser(*other);
						}

					}
				}
			}
		}
	}
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

	////UIの解放
	//for (auto& obj : GameUIs) {
	//	obj->Destroy();
	//}
	//GameUIs.clear();

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
