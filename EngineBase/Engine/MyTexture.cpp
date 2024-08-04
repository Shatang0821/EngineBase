#include "stdafx.h"
#include "MyTexture.h"

MyTexture* MyTexture::sm_pStack[MAX_TEXTURE];
int MyTexture::sm_maxTexture = 0;

HRESULT LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname, IDirect3DTexture9** ppTex)
{
    //パワーオブツー（2の累乗）に調整しているです
	//HRESULT hr = D3DXCreateTextureFromFile(pDev, pFname, ppTex);
    //非パワーオブツーテクスチャを読み込む
    HRESULT hr = D3DXCreateTextureFromFileEx(
        pDev,
        pFname,
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        NULL,
        NULL,
        ppTex
    );
	if (FAILED(hr))
	{
		// 失敗したので一つ上のフォルダからテクスチャを探してみる.
		int flen = (int)_tcslen(pFname) + 4;
		_tprintf(_T("%s: 親ディレクトリから探索...\n"), pFname);
		TCHAR* fn = new TCHAR[flen];
		_stprintf_s(fn, flen, _T("..\\%s"), pFname);
		//hr = D3DXCreateTextureFromFile(pDev, fn, ppTex);
        hr = D3DXCreateTextureFromFileEx(
            pDev,
            pFname,
            D3DX_DEFAULT_NONPOW2,
            D3DX_DEFAULT_NONPOW2,
            D3DX_DEFAULT,
            0,
            D3DFMT_UNKNOWN,
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            0,
            NULL,
            NULL,
            ppTex
        );
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
		delete pMyTex;
		return NULL;
	}

	pMyTex->m_width = desc.Width;
	pMyTex->m_height = desc.Height;

	sm_pStack[sm_maxTexture++] = pMyTex;// スタックに積む.
	return pMyTex;
}

MyTexture* MyTexture::CreateSprite(IDirect3DDevice9* pDev, const TCHAR* pFname, float u1, float v1, float u2, float v2)
{
    if (sm_maxTexture >= MAX_TEXTURE)
    {
        return NULL;
    }

    // オブジェクトを生成
    MyTexture* pMyTex = new MyTexture;

    // スプライトシート全体を読み込む
    if (FAILED(::LoadTexture(pDev, pFname, &(pMyTex->m_pTex))))
    {
        MessageBox(NULL, _T("スプライトシート取得失敗"), pFname, MB_OK);
        delete pMyTex;
        return NULL;
    }

    // テクスチャの詳細情報を取得
    D3DSURFACE_DESC desc;
    if (FAILED(pMyTex->m_pTex->GetLevelDesc(0, &desc)))
    {
        MessageBox(NULL, _T("テクスチャデータ取得失敗"), pFname, MB_OK);
        delete pMyTex;
        return NULL;
    }

    // スプライトの座標をピクセル単位に変換
    int srcX1 = static_cast<int>(u1 * desc.Width);
    int srcY1 = static_cast<int>(v1 * desc.Height);
    int srcX2 = static_cast<int>(u2 * desc.Width);
    int srcY2 = static_cast<int>(v2 * desc.Height);
    int width = srcX2 - srcX1;
    int height = srcY2 - srcY1;

    // 新しいテクスチャを作成
    IDirect3DTexture9* pNewTex = nullptr;
    if (FAILED(pDev->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, desc.Format, D3DPOOL_DEFAULT, &pNewTex, NULL)))
    {
        MessageBox(NULL, _T("新しいテクスチャ作成失敗"), pFname, MB_OK);
        delete pMyTex;
        return NULL;
    }

    // 元のテクスチャから新しいテクスチャにコピー
    IDirect3DSurface9* pSrcSurface = nullptr;
    IDirect3DSurface9* pDstSurface = nullptr;
    pMyTex->m_pTex->GetSurfaceLevel(0, &pSrcSurface);
    pNewTex->GetSurfaceLevel(0, &pDstSurface);

    RECT srcRect = { srcX1, srcY1, srcX2, srcY2 };
    if (FAILED(D3DXLoadSurfaceFromSurface(pDstSurface, NULL, NULL, pSrcSurface, NULL, &srcRect, D3DX_DEFAULT, 0)))
    {
        MessageBox(NULL, _T("テクスチャコピー失敗"), pFname, MB_OK);
        pSrcSurface->Release();
        pDstSurface->Release();
        pNewTex->Release();
        delete pMyTex;
        return NULL;
    }

    pSrcSurface->Release();
    pDstSurface->Release();

    // 新しいテクスチャをMyTextureオブジェクトに設定
    pMyTex->m_pTex = pNewTex;
    pMyTex->m_width = width;
    pMyTex->m_height = height;

    // スタックに積む
    sm_pStack[sm_maxTexture++] = pMyTex;
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
