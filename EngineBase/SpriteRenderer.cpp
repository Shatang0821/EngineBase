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
	//中心点の計算
	D3DXVECTOR3 center(sprite->GetWidth() / 2, sprite->GetHeight() / 2, 1.0);

	// スケーリング行列を初期化
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	// スケーリング行列を設定
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);

	// 平行移動行列を設定
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, pos.x + center.x , pos.y + center.y, 0.0f);

	// スプライトに変換行列を設定
	pSprite->SetTransform(&mat);

	pSprite->Draw(sprite->GetTexture(), NULL, &center, &position, D3DCOLOR_XRGB(255, 255, 255));
	// スプライトの変換行列をリセット（他の描画に影響を与えないようにするため）
	D3DXMatrixIdentity(&mat);
	pSprite->SetTransform(&mat);
}