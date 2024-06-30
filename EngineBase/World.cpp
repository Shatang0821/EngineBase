#include "stdafx.h"
#include "World.h"
#include "Timer.h"

World mainWorld;

void World::Update(float DeltaTime)
{
	//���x���̍X�V
	currentLevel->Update(DeltaTime);

	//�J�����̍X�V
	mainCamera->Calculate();

	//�I�u�W�F�N�g�̍X�V
	for (auto& obj : GameObjects) {
		obj->Update(DeltaTime);
	}
	//�폜�\��̃I�u�W�F�N�g���폜����
	for (auto& obj : GameObjects_to_delete) {
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
