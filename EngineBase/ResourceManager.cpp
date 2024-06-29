#include "stdafx.h"
#include "ResourceManager.h"
#include "myApp.h"

void ResourceManager::LoadTex(IDirect3DDevice9* pDev,ResID id, const TCHAR* pFname)
{
	//�e�N�X�`���̎擾
	auto tex = MyTexture::LoadTexture(pDev, pFname);
	//�v�[���ɍ�������
	imagePool.insert(std::pair<ResID,MyTexture*>(id,tex));
}

void ResourceManager::Initalize()
{
	auto myApp = MyApp::Instance();
	auto device = myApp->GetDevice();
	LoadTex(device, ResID::Tex_Bullet, _T("data/image/bullet.png"));
}

MyTexture* ResourceManager::Fetch(ResID id)
{
	if (auto it = imagePool.find(id);it != imagePool.end()) {
		return it->second;
	}
	return nullptr;
}
