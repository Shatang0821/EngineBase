#include "stdafx.h"
#include "SpriteRenderer.h"
#include "myApp.h"
#include "Camera.h"

void SpriteRenderer::Render()
{
    auto pSprite = MyApp::Instance()->GetSprite();
    auto p = GetWorldPosition() - mainWorld.mainCamera->GetCameraPosition();
    D3DXVECTOR3 position(p.x, p.y, 0);
    float rot = GetWorldRotation();
    Vector2 scale = GetWorldScale();

    // ���S�_�̌v�Z
    D3DXVECTOR3 center(sprite->GetWidth() / 2, sprite->GetHeight() / 2, 0.0f);

    // �X�P�[�����O�s���������
    D3DXMATRIX matScale;
    D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);

    // ��]�s���������
    D3DXMATRIX matRotation;
    D3DXMatrixRotationZ(&matRotation, D3DXToRadian(rot));

    // ���s�ړ��s���������
    D3DXMATRIX matTranslation;
    D3DXMatrixTranslation(&matTranslation, position.x, position.y, 0.0f);

    // �X�P�[�����O�A��]�A���s�ړ��s���g�ݍ��킹��
    D3DXMATRIX matTransform = matScale * matRotation * matTranslation;

    // �X�v���C�g�ɕϊ��s���ݒ�
    pSprite->SetTransform(&matTransform);

    // �X�v���C�g��`��
    pSprite->Draw(sprite->GetTexture(), NULL, &center, NULL, D3DCOLOR_XRGB(255, 255, 255));

    // �X�v���C�g�̕ϊ��s������Z�b�g�i���̕`��ɉe����^���Ȃ��悤�ɂ��邽�߁j
    D3DXMatrixIdentity(&matTransform);
    pSprite->SetTransform(&matTransform);
}