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
        // 角度の取得ラジアン
        float rot = D3DXToRadian(GetWorldRotation());

        Vector2 scaleVec = GetWorldScale();
        // 2.0fはスプライトのサイズを画面サイズに合わせるための係数
        D3DXVECTOR2 scale(scaleVec.x * 2.0f / mainWorld.mainCamera->springArmLength_virtual, scaleVec.y * 2.0f / mainWorld.mainCamera->springArmLength_virtual);

        // 中心点の計算
        D3DXVECTOR2 center(sprite->GetWidth() / 2, sprite->GetHeight() / 2);

        // 変換行列の計算  
        D3DXMATRIX matTransform;
        D3DXMatrixTransformation2D(&matTransform, &center, 0, &scale, &center, rot, &position);

        // スプライトに変換行列を設定
        pSprite->SetTransform(&matTransform);

        // フィルターモードを「Point」に設定
        auto pDevice = MyApp::Instance()->GetDevice();
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

        // スプライトを描画
        // 透明、フィールドの色を反映するためにD3DCOLOR_RGBA(255, 255, 255, 255)を使用今後変数にする
        pSprite->Draw(sprite->GetTexture(), NULL, NULL, NULL, D3DCOLOR_RGBA(255, 255, 255,255));

        // スプライトの変換行列をリセット（他の描画に影響を与えないようにするため）
        pSprite->SetTransform(nullptr);
    }
}