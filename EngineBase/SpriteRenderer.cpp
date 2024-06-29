#include "stdafx.h"
#include "SpriteRenderer.h"
#include "myApp.h"


void SpriteRenderer::Render()
{
	auto pSprite = MyApp::Instance()->GetSprite();
	Vector2 pos = GetWorldPosition();
	D3DXVECTOR3 position(pos.x,pos.y,0);
	float rot = GetWorldRotation();
	Vector2 scale = GetWorldScale();
	//���S�_�̌v�Z
	D3DXVECTOR3 center(sprite->GetWidth() / 2, sprite->GetHeight() / 2, 1.0);

	// �X�P�[�����O�s���������
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	// �X�P�[�����O�s���ݒ�
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);

	// ���s�ړ��s���ݒ�
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, pos.x + center.x , pos.y + center.y, 0.0f);

	// �X�v���C�g�ɕϊ��s���ݒ�
	pSprite->SetTransform(&mat);

	pSprite->Draw(sprite->GetTexture(), NULL, &center, &position, D3DCOLOR_XRGB(255, 255, 255));
	// �X�v���C�g�̕ϊ��s������Z�b�g�i���̕`��ɉe����^���Ȃ��悤�ɂ��邽�߁j
	D3DXMatrixIdentity(&mat);
	pSprite->SetTransform(&mat);
}