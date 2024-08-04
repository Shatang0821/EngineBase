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
	//�R���g���[���[�̐���
	mainWorld.mainController = GameStatics::CreateObject<GameController>();
	//���[���h������
	mainWorld.currentLevel = new GameLevel;
	mainWorld.gameInstance = new GameInstance;


	return true;
}

void World::Update(float DeltaTime)
{
	//���x���̍X�V
	currentLevel->Update(DeltaTime);

	//�I�u�W�F�N�g�̍X�V
	for (auto& obj : GameObjects) {
		if(obj != nullptr)
			obj->Update(DeltaTime);
	}
	//�I�u�W�F�N�g�̒ǉ�
	for(auto& obj : GameObjects_to_add)
	{
		GameObjects.insert(obj);
		obj->BeginPlay();
	}
	GameObjects_to_add.clear();

	//�폜�\��̃I�u�W�F�N�g���폜����
	for (auto& obj : GameObjects_to_delete) {
		delete obj;
		GameObjects.erase(obj);
	}
	//�R���e�i���N���A
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
	//�����X�V
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
	swprintf(text, 50, L"%u", fps); // ���l�𕶎���ɕϊ�
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
	//�I�u�W�F�N�g�̉��
	for (auto obj : GameObjects) {
		obj->Destroy();

	}
	//�R���e�i���N���A
	GameObjects.clear();

	for (auto obj : GameObjects_to_delete) {
		delete obj;
	}
	GameObjects_to_delete.clear();

	//�^�C�}�[�̉��
	for (auto obj : GameTimers) {
		delete obj;
	}
	GameTimers.clear();

	//�폜�\��̃I�u�W�F�N�g���폜����
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
