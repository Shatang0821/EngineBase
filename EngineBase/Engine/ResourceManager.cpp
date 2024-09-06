#include "stdafx.h"
#include "ResourceManager.h"
#include "myApp.h"

bool ResourceManager::LoadTex(IDirect3DDevice9* pDev,ResID id, const TCHAR* pFname)
{
	//テクスチャの取得
	auto tex = MyTexture::LoadTexture(pDev, pFname);
	if (tex)
	{
		//プールに差し込む
		imagePool.insert(std::pair<ResID, MyTexture*>(id, tex));
        return true;
	}
    return false;
	
}

bool ResourceManager::LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname, int num)
{
	std::vector<MyTexture*> texs;

    for(int i = 0; i < num; i++)
    {
        //テクスチャの取得
        TCHAR fname[256];
		//パス名が pFname_1 というように連番であることを想定
        _stprintf_s(fname, _T("%s_%d.png"), pFname, i+1);
        auto tex = MyTexture::LoadTexture(pDev, fname);
		if (tex) {
			texs.push_back(tex);
		}
        else {
            return false;
        }
    }
    //プールに差し込む
    animPool.insert({id,{texs,num}});
    return true;
}

bool ResourceManager::LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname, int num, int row, int col,int texWidth,int texHeight)
{
    std::vector<MyTexture*> texs;

    for (int i = 0; i < num; i++)
    {
        // スプライトのインデックスを計算
        int spriteRow = i / col; // 現在のスプライトが何行目にあるか
        int spriteCol = i % col; // 現在のスプライトが何列目にあるか

        // スプライトのサイズを計算
        int spriteWidth = texWidth / col;
        int spriteHeight = texHeight / row;

        // スプライトのUV座標を計算
        float u1 = spriteCol * spriteWidth / (float)texWidth;
        float v1 = spriteRow * spriteHeight / (float)texHeight;
        float u2 = (spriteCol + 1) * spriteWidth / (float)texWidth;
        float v2 = (spriteRow + 1) * spriteHeight / (float)texHeight;

        // スプライトを作成
        auto tex = MyTexture::CreateSprite(pDev, pFname, u1, v1, u2, v2);
        if (tex) {
            texs.push_back(tex);
        }
        else {
            return false;
        }
    }

    // Insert the sprite sheet into the animation pool
    animPool.insert({ id,{texs,num} });
    return true;
}

bool ResourceManager::Initalize()
{
	auto myApp = MyApp::Instance();
	auto device = myApp->GetDevice();

    assert(LoadTex(device, ResID::Tex_Player_Idle, _T("data/image/Samurai/IDLE.png"), 5, 1, 5, 500, 44));
    assert(LoadTex(device, ResID::Tex_Player_Run, _T("data/image/Samurai/RUN.png"), 7, 1, 7, 700, 44));
    assert(LoadTex(device, ResID::Tex_Player_Jump, _T("data/image/Samurai/JUMP.png"), 1, 1, 1, 100, 44));
    assert(LoadTex(device, ResID::Tex_Player_Fall, _T("data/image/Samurai/FALL.png"), 2, 1, 2, 200, 44));

    return true;
}

MyTexture* ResourceManager::Fetch(ResID id)
{
	if (auto it = imagePool.find(id);it != imagePool.end()) {
		return it->second;
	}
	return nullptr;
}

AnimationResource ResourceManager::FetchAnim(ResID id)
{
    if(auto it = animPool.find(id);it != animPool.end())
	{
		return it->second;
	}
    return AnimationResource();
}
