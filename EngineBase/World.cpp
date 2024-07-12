#include "stdafx.h"
#include "World.h"
#include "Timer.h"
#include "InputManager.h"
#include "MyApp.h"

World mainWorld;

void World::Update(float DeltaTime)
{
	//レベルの更新
	currentLevel->Update(DeltaTime);

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
	Debug();
}

void World::Input()
{
	//mainController->PickInfo();
	InputManager::Instance()->UpdateInput(MyApp::Instance()->GetHWND());
}

// テキストの描画
void RenderText(IDirect3DDevice9* pDevice, int x, int y, const wchar_t* text)
{
	RECT rect;
	SetRect(&rect, x, y, x + 300, y + 50); // テキストを描画する矩形範囲

	// テキストの描画
	MyApp::Instance()->GetFont()->DrawTextW(
		NULL,            // スプライトオブジェクトへのポインタ（使用しないのでNULL）
		text,            // 描画するテキスト
		-1,              // テキストの長さ（-1はNULL終端まで）
		&rect,           // 描画する矩形範囲
		DT_LEFT | DT_TOP,// テキストの配置
		D3DCOLOR_XRGB(255, 255, 255) // テキストのカラー
	);
}

void World::Debug()
{
	wchar_t text[50];
	swprintf(text, 50, L"%u", fps); // 数値を文字列に変換
	RenderText(MyApp::Instance()->GetDevice(), 0, 0,text);
}
