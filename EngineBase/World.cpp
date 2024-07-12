#include "stdafx.h"
#include "World.h"
#include "Timer.h"
#include "InputManager.h"
#include "MyApp.h"

World mainWorld;

void World::Update(float DeltaTime)
{
	//���x���̍X�V
	currentLevel->Update(DeltaTime);

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
	Debug();
}

void World::Input()
{
	//mainController->PickInfo();
	InputManager::Instance()->UpdateInput(MyApp::Instance()->GetHWND());
}

// �e�L�X�g�̕`��
void RenderText(IDirect3DDevice9* pDevice, int x, int y, const wchar_t* text)
{
	RECT rect;
	SetRect(&rect, x, y, x + 300, y + 50); // �e�L�X�g��`�悷���`�͈�

	// �e�L�X�g�̕`��
	MyApp::Instance()->GetFont()->DrawTextW(
		NULL,            // �X�v���C�g�I�u�W�F�N�g�ւ̃|�C���^�i�g�p���Ȃ��̂�NULL�j
		text,            // �`�悷��e�L�X�g
		-1,              // �e�L�X�g�̒����i-1��NULL�I�[�܂Łj
		&rect,           // �`�悷���`�͈�
		DT_LEFT | DT_TOP,// �e�L�X�g�̔z�u
		D3DCOLOR_XRGB(255, 255, 255) // �e�L�X�g�̃J���[
	);
}

void World::Debug()
{
	wchar_t text[50];
	swprintf(text, 50, L"%u", fps); // ���l�𕶎���ɕϊ�
	RenderText(MyApp::Instance()->GetDevice(), 0, 0,text);
}
