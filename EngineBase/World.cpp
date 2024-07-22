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
	//���[���h������
	mainWorld.currentLevel = new GameLevel;
	mainWorld.gameInstance = new GameInstance;

	//mainWorld.mainController = new Controller;
	mainWorld.mainController = GameStatics::CreateObject<GameController>();

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
	//���x���̕����X�V
	for (auto& arr_i : ColliderZones)
		for (auto& arr_j : arr_i)
			arr_j.clear();

	for(auto it = GameColliders.begin(); it != GameColliders.end(); ++it)
	{
		//�O�t���[���̏Փˏ����N���A
		(*it)->Clear();

		//�R���C�_�[���������擾
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

		//����̍��W���擾
		Vector2 pos = (*it)->GetWorldPosition();
		pos -= half;

		int x = int(pos.x) / 100; x = Math::clamp(x, 0, 7);
		int y = int(pos.y) / 100; y = Math::clamp(y, 0, 5);

		//�E���̍��W���擾
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

	//�R���C�_�[�̕����X�V
	for (auto& arr_i : ColliderZones) {
		for (auto& arr_j : arr_i)
		{
			if (!arr_j.empty())
			{
				for (auto me = arr_j.begin(); me != arr_j.end(); ++me)
				{
					//�����ȊO�̃R���C�_�[�Ɣ���
					for (auto other = arr_j.begin(); other != arr_j.end(); ++other)
					{
						if (other != me) {
							//�Փ˔���
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

	////UI�̉��
	//for (auto& obj : GameUIs) {
	//	obj->Destroy();
	//}
	//GameUIs.clear();

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
