#include "stdafx.h"
#include "MyTexture.h"

MyTexture* MyTexture::sm_pStack[MAX_TEXTURE];
int MyTexture::sm_maxTexture = 0;

HRESULT LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname, IDirect3DTexture9** ppTex)
{
	HRESULT hr = D3DXCreateTextureFromFile(pDev, pFname, ppTex);
	if (FAILED(hr))
	{
		// ���s�����̂ň��̃t�H���_����e�N�X�`����T���Ă݂�.
		int flen = (int)_tcslen(pFname) + 4;
		_tprintf(_T("%s: �e�f�B���N�g������T��...\n"), pFname);
		TCHAR* fn = new TCHAR[flen];
		_stprintf_s(fn, flen, _T("..\\%s"), pFname);
		hr = D3DXCreateTextureFromFile(pDev, fn, ppTex);
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
	}

	pMyTex->m_width = desc.Width;
	pMyTex->m_height = desc.Height;

	sm_pStack[sm_maxTexture++] = pMyTex;// �X�^�b�N�ɐς�.
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
