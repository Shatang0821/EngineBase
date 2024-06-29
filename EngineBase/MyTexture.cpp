#include "stdafx.h"
#include "MyTexture.h"

MyTexture* MyTexture::sm_pStack[MAX_TEXTURE];
int MyTexture::sm_maxTexture = 0;

HRESULT LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname, IDirect3DTexture9** ppTex)
{
	HRESULT hr = D3DXCreateTextureFromFile(pDev, pFname, ppTex);
	if (FAILED(hr))
	{
		// 失敗したので一つ上のフォルダからテクスチャを探してみる.
		int flen = (int)_tcslen(pFname) + 4;
		_tprintf(_T("%s: 親ディレクトリから探索...\n"), pFname);
		TCHAR* fn = new TCHAR[flen];
		_stprintf_s(fn, flen, _T("..\\%s"), pFname);
		hr = D3DXCreateTextureFromFile(pDev, fn, ppTex);
		delete[] fn;
		if (FAILED(hr))
		{
			// 失敗したので例外を発生させて終わる.
			MessageBox(NULL, _T("テクスチャ読み込み失敗"), pFname, MB_OK);
			throw hr;		// エラーが発生したので例外を送る.
		}
	}
	return hr;
}


MyTexture* MyTexture::LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname)
{
	if (sm_maxTexture >= MAX_TEXTURE)
	{
		return NULL;
	}

	// オブジェクトを生成.
	MyTexture* pMyTex = new MyTexture;
	// ::だけが付いた関数はグローバル関数を呼び出すことを意味する.
	::LoadTexture(pDev, pFname, &(pMyTex->m_pTex));

	// テクスチャの詳細情報を取得
	D3DSURFACE_DESC desc;
	if (FAILED(pMyTex->m_pTex->GetLevelDesc(0, &desc)))
	{
		MessageBox(NULL, _T("テクスチャデータ取得失敗"), pFname, MB_OK);
	}

	pMyTex->m_width = desc.Width;
	pMyTex->m_height = desc.Height;

	sm_pStack[sm_maxTexture++] = pMyTex;// スタックに積む.
	return pMyTex;
}

void MyTexture::ReleaseAll()
{
	for (int i = sm_maxTexture - 1; i >= 0; i--)
	{
		if (sm_pStack[i])
		{
			delete sm_pStack[i];
		}
		sm_pStack[i] = NULL;
	}
	sm_maxTexture = 0;
}
