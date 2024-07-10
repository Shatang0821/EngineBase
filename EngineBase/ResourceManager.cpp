#include "stdafx.h"
#include "ResourceManager.h"
#include "myApp.h"

void ResourceManager::LoadTex(IDirect3DDevice9* pDev,ResID id, const TCHAR* pFname)
{
	//�e�N�X�`���̎擾
	auto tex = MyTexture::LoadTexture(pDev, pFname);
	if (tex)
	{
		//�v�[���ɍ�������
		imagePool.insert(std::pair<ResID, MyTexture*>(id, tex));
	}
	else {
		printf("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���\n");
	}
	
}

void ResourceManager::LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname, int num)
{
	std::vector<MyTexture*> texs;

    for(int i = 0; i < num; i++)
    {
        //�e�N�X�`���̎擾
        TCHAR fname[256];
		//�p�X���� pFname_1 �Ƃ����悤�ɘA�Ԃł��邱�Ƃ�z��
        _stprintf_s(fname, _T("%s_%d.png"), pFname, i+1);
        auto tex = MyTexture::LoadTexture(pDev, fname);
		if (tex) {
			texs.push_back(tex);
		}
    }
    //�v�[���ɍ�������
    animPool.insert({id,{texs,num}});
}

void ResourceManager::LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname, int num, int row, int col,int texWidth,int texHeight)
{
    std::vector<MyTexture*> texs;

    for (int i = 0; i < num; i++)
    {
        // �X�v���C�g�̃C���f�b�N�X���v�Z
        int spriteRow = i / col; // ���݂̃X�v���C�g�����s�ڂɂ��邩
        int spriteCol = i % col; // ���݂̃X�v���C�g������ڂɂ��邩

        // �X�v���C�g�̃T�C�Y���v�Z
        int spriteWidth = texWidth / col;
        int spriteHeight = texHeight / row;

        // �X�v���C�g��UV���W���v�Z
        float u1 = spriteCol * spriteWidth / (float)texWidth;
        float v1 = spriteRow * spriteHeight / (float)texHeight;
        float u2 = (spriteCol + 1) * spriteWidth / (float)texWidth;
        float v2 = (spriteRow + 1) * spriteHeight / (float)texHeight;

        // �X�v���C�g���쐬
        auto tex = MyTexture::CreateSprite(pDev, pFname, u1, v1, u2, v2);
        if (tex) {
            texs.push_back(tex);
        }
    }

    // Insert the sprite sheet into the animation pool
    animPool.insert({ id,{texs,num} });
}

void ResourceManager::Initalize()
{
	auto myApp = MyApp::Instance();
	auto device = myApp->GetDevice();
	LoadTex(device, ResID::Tex_Bullet, _T("data/image/parallax-mountain-bg.png"));
    LoadTex(device, ResID::Tex_Player, _T("data/image/Virtual Guy/Idle (32x32).png"),11,1,11,352,32);
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
