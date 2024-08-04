#include "stdafx.h"
#include "myApp.h"
#include "StaticMesh.h"
#include "ResourceManager.h"
#include "../GameLevel.h"
#include "../GameController.h"
#include "InputManager.h"

// �C�x���g�����R�[���o�b�N�i�E�B���h�E�v���V�[�W���j.
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �C�x���g�̎�ނɉ����āAswitch���ɂď�����؂蕪����.
	switch (uMsg) {
	case WM_KEYDOWN: {
		// ESC�L�[���������ꂽ��I��.
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		break;
	}

	case WM_CLOSE: {// �I���ʒm(CLOSE�{�^���������ꂽ�ꍇ�Ȃ�)���͂����ꍇ.
		// �v���O�������I�������邽�߁A�C�x���g���[�v��0��ʒm����.
		// ���̌��ʁAGetMessage�̖߂�l��0�ɂȂ�.
		PostQuitMessage(0);
		break;
	}

	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			MyApp::Instance()->ResizeWindow(width, height);
		}
		break;
	default: {
		break;
	}
	}

	// �f�t�H���g�̃E�B���h�E�C�x���g����.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
// �G���[��������HRESULT�𕶎���ɕϊ����邽�߂̕⏕�֐�.
const TCHAR* D3DErrStr(HRESULT res)
{
	switch (res) {
	case D3D_OK: return _T("D3D_OK");
	case D3DERR_DEVICELOST: return _T("D3DERR_DEVICELOST");
	case D3DERR_DRIVERINTERNALERROR: return _T("D3DERR_DRIVERINTERNALERROR");
	case D3DERR_INVALIDCALL: return _T("D3DERR_INVALIDCALL");
	case D3DERR_OUTOFVIDEOMEMORY: return _T("D3DERR_OUTOFVIDEOMEMORY");
	case D3DERR_DEVICENOTRESET: return _T("D3DERR_DEVICENOTRESET");
	case D3DERR_NOTAVAILABLE: return _T("D3DERR_NOTAVAILABLE");
	case D3DXERR_INVALIDDATA: return _T("D3DXERR_INVALIDDATA");
	case MMSYSERR_NODRIVER: return _T("MMSYSERR_NODRIVER");
	case MMSYSERR_INVALPARAM: return _T("MMSYSERR_INVALPARAM");
	case MMSYSERR_BADDEVICEID: return _T("MMSYSERR_BADDEVICEID");
	case JOYERR_UNPLUGGED: return _T("JOYERR_UNPLUGGED");
	case JOYERR_PARMS: return _T("JOYERR_PARMS");
	case E_OUTOFMEMORY: return _T("E_OUTOFMEMORY");
	}
	return _T("unknown error");
}


int main() {
	setlocale(LC_ALL, "Japanese");		// ���{��Ƀ��P�[����ݒ�.

#ifdef MEMORY_LEAK
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	if(MyApp::Instance()->InitDirectX() == false) {
		_tprintf(_T("DirectX�̏������Ɏ��s���܂����B\n"));
		return -1;
	}
	if(MyApp::Instance()->InitGame() == false) {
		_tprintf(_T("�Q�[���̏������Ɏ��s���܂����B\n"));
		return -1;
	}
	ShowWindow(MyApp::Instance()->GetHWND(), SW_SHOWNORMAL);	// �쐬�����E�B���h�E��\������.

	MyApp::Instance()->MainLoop();

	MyApp::Instance()->ReleaseData();

#ifdef MEMORY_LEAK
	_CrtDumpMemoryLeaks();		// ���������[�N�����o����.
#endif
	return 0;
}