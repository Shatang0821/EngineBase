#include "stdafx.h"
#include "MyTexture.h"

MyTexture* MyTexture::sm_pStack[MAX_TEXTURE];
int MyTexture::sm_maxTexture = 0;

HRESULT LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname, IDirect3DTexture9** ppTex)
{
    //�p���[�I�u�c�[�i2�̗ݏ�j�ɒ������Ă���ł�
	//HRESULT hr = D3DXCreateTextureFromFile(pDev, pFname, ppTex);
    //��p���[�I�u�c�[�e�N�X�`����ǂݍ���
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
		// ���s�����̂ň��̃t�H���_����e�N�X�`����T���Ă݂�.
		int flen = (int)_tcslen(pFname) + 4;
		_tprintf(_T("%s: �e�f�B���N�g������T��...\n"), pFname);
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
			// ���s�����̂ŗ�O�𔭐������ďI���.
			MessageBox(NULL, _T("�e�N�X�`���ǂݍ��ݎ��s"), pFname, MB_OK);
			throw hr;		// �G���[�����������̂ŗ�O�𑗂�.
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

	// �I�u�W�F�N�g�𐶐�.
	MyTexture* pMyTex = new MyTexture;
	// ::�������t�����֐��̓O���[�o���֐����Ăяo�����Ƃ��Ӗ�����.
	::LoadTexture(pDev, pFname, &(pMyTex->m_pTex));

	// �e�N�X�`���̏ڍ׏����擾
	D3DSURFACE_DESC desc;
	if (FAILED(pMyTex->m_pTex->GetLevelDesc(0, &desc)))
	{
		MessageBox(NULL, _T("�e�N�X�`���f�[�^�擾���s"), pFname, MB_OK);
		delete pMyTex;
		return NULL;
	}

	pMyTex->m_width = desc.Width;
	pMyTex->m_height = desc.Height;

	sm_pStack[sm_maxTexture++] = pMyTex;// �X�^�b�N�ɐς�.
	return pMyTex;
}

MyTexture* MyTexture::CreateSprite(IDirect3DDevice9* pDev, const TCHAR* pFname, float u1, float v1, float u2, float v2)
{
    if (sm_maxTexture >= MAX_TEXTURE)
    {
        return NULL;
    }

    // �I�u�W�F�N�g�𐶐�
    MyTexture* pMyTex = new MyTexture;

    // �X�v���C�g�V�[�g�S�̂�ǂݍ���
    if (FAILED(::LoadTexture(pDev, pFname, &(pMyTex->m_pTex))))
    {
        MessageBox(NULL, _T("�X�v���C�g�V�[�g�擾���s"), pFname, MB_OK);
        delete pMyTex;
        return NULL;
    }

    // �e�N�X�`���̏ڍ׏����擾
    D3DSURFACE_DESC desc;
    if (FAILED(pMyTex->m_pTex->GetLevelDesc(0, &desc)))
    {
        MessageBox(NULL, _T("�e�N�X�`���f�[�^�擾���s"), pFname, MB_OK);
        delete pMyTex;
        return NULL;
    }

    // �X�v���C�g�̍��W���s�N�Z���P�ʂɕϊ�
    int srcX1 = static_cast<int>(u1 * desc.Width);
    int srcY1 = static_cast<int>(v1 * desc.Height);
    int srcX2 = static_cast<int>(u2 * desc.Width);
    int srcY2 = static_cast<int>(v2 * desc.Height);
    int width = srcX2 - srcX1;
    int height = srcY2 - srcY1;

    // �V�����e�N�X�`�����쐬
    IDirect3DTexture9* pNewTex = nullptr;
    if (FAILED(pDev->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, desc.Format, D3DPOOL_DEFAULT, &pNewTex, NULL)))
    {
        MessageBox(NULL, _T("�V�����e�N�X�`���쐬���s"), pFname, MB_OK);
        delete pMyTex;
        return NULL;
    }

    // ���̃e�N�X�`������V�����e�N�X�`���ɃR�s�[
    IDirect3DSurface9* pSrcSurface = nullptr;
    IDirect3DSurface9* pDstSurface = nullptr;
    pMyTex->m_pTex->GetSurfaceLevel(0, &pSrcSurface);
    pNewTex->GetSurfaceLevel(0, &pDstSurface);

    RECT srcRect = { srcX1, srcY1, srcX2, srcY2 };
    if (FAILED(D3DXLoadSurfaceFromSurface(pDstSurface, NULL, NULL, pSrcSurface, NULL, &srcRect, D3DX_DEFAULT, 0)))
    {
        MessageBox(NULL, _T("�e�N�X�`���R�s�[���s"), pFname, MB_OK);
        pSrcSurface->Release();
        pDstSurface->Release();
        pNewTex->Release();
        delete pMyTex;
        return NULL;
    }

    pSrcSurface->Release();
    pDstSurface->Release();

    // �V�����e�N�X�`����MyTexture�I�u�W�F�N�g�ɐݒ�
    pMyTex->m_pTex = pNewTex;
    pMyTex->m_width = width;
    pMyTex->m_height = height;

    // �X�^�b�N�ɐς�
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
