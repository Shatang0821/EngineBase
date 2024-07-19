#include "stdafx.h"
#include "SpriteRenderer.h"
#include "myApp.h"
#include "Camera.h"

void SpriteRenderer::Render()
{    
    if (sprite) {
        auto pSprite = MyApp::Instance()->GetSprite();
        auto p = GetWorldPosition() - mainWorld.mainCamera->GetCameraPosition() + Vector2(WIDTH / 2,HEIGHT / 2);
        auto size = Vector2(GetSpriteWidth(), GetSpriteHeight());
        D3DXVECTOR2 position(p.x - size.x / 2, p.y - size.y /2);
        // �p�x�̎擾���W�A��
        float rot = D3DXToRadian(GetWorldRotation());

        Vector2 scaleVec = GetWorldScale();
        // 2.0f�̓X�v���C�g�̃T�C�Y����ʃT�C�Y�ɍ��킹�邽�߂̌W��
        D3DXVECTOR2 scale(scaleVec.x * 2.0f / mainWorld.mainCamera->springArmLength_virtual, scaleVec.y * 2.0f / mainWorld.mainCamera->springArmLength_virtual);

        // ���S�_�̌v�Z
        D3DXVECTOR2 center(sprite->GetWidth() / 2, sprite->GetHeight() / 2);

        // �ϊ��s��̌v�Z  
        D3DXMATRIX matTransform;
        D3DXMatrixTransformation2D(&matTransform, &center, 0, &scale, &center, rot, &position);

        // �X�v���C�g�ɕϊ��s���ݒ�
        pSprite->SetTransform(&matTransform);

        // �t�B���^�[���[�h���uPoint�v�ɐݒ�
        auto pDevice = MyApp::Instance()->GetDevice();
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

        // �X�v���C�g��`��
        // �����A�t�B�[���h�̐F�𔽉f���邽�߂�D3DCOLOR_RGBA(255, 255, 255, 255)���g�p����ϐ��ɂ���
        pSprite->Draw(sprite->GetTexture(), NULL, NULL, NULL, D3DCOLOR_RGBA(255, 255, 255,255));

        // �X�v���C�g�̕ϊ��s������Z�b�g�i���̕`��ɉe����^���Ȃ��悤�ɂ��邽�߁j
        pSprite->SetTransform(nullptr);
    }
}