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

    // 中心点の計算
    D3DXVECTOR3 center(sprite->GetWidth() / 2, sprite->GetHeight() / 2, 0.0f);

    // スケーリング行列を初期化
    D3DXMATRIX matScale;
    D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);

    // 回転行列を初期化
    D3DXMATRIX matRotation;
    D3DXMatrixRotationZ(&matRotation, D3DXToRadian(rot));

    // 平行移動行列を初期化
    D3DXMATRIX matTranslation;
    D3DXMatrixTranslation(&matTranslation, position.x, position.y, 0.0f);

    // スケーリング、回転、平行移動行列を組み合わせる
    D3DXMATRIX matTransform = matScale * matRotation * matTranslation;

    // スプライトに変換行列を設定
    pSprite->SetTransform(&matTransform);

    // スプライトを描画
    pSprite->Draw(sprite->GetTexture(), NULL, &center, NULL, D3DCOLOR_XRGB(255, 255, 255));

    // スプライトの変換行列をリセット（他の描画に影響を与えないようにするため）
    D3DXMatrixIdentity(&matTransform);
    pSprite->SetTransform(&matTransform);
}