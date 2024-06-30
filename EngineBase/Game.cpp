#include "stdafx.h"
#include "myApp.h"
#include "StaticMesh.h"
#include "ResourceManager.h"
#include "GameLevel.h"
#include "GameController.h"

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

class Engine
{
public:
	/**
	 * @brief �G���W������������
	 */
	static void Init()
	{
		// ���C�u����������
		MyApp::Instance()->InitApp();
		//Engine������
		ResourceManager::Instance()->Initalize();
		//���[���h������
		mainWorld.currentLevel = new GameLevel;
		mainWorld.gameInstance = new GameInstance;

		//mainWorld.mainController = new Controller;
		mainWorld.mainController = GameStatics::CreateObject<GameController>();
	}

	/**
	 * @brief �G���W���X�V����
	 */
	static void Tick()
	{

		// �t���[���J�n���̃^�C�}�[���Z�b�g
		mainWorld.Timer.StartTimer();

		// ���͏���
		mainWorld.Input();

		// �Œ莞�ԃX�e�b�v�ł̕����X�V
		mainWorld.fixedAccumulator += mainWorld.deltaTime;
		while (mainWorld.fixedAccumulator >= FIXED_DELTA_TIME)
		{
			mainWorld.FixedUpdate();
			mainWorld.fixedAccumulator -= FIXED_DELTA_TIME;
		}

		// ���W�b�N�X�V
		mainWorld.Update(mainWorld.deltaTime);

		// �`��̏���
		MyApp::Instance()->DrawStart();

		// �`�揈��
		mainWorld.Render();

		// �`��I��
		MyApp::Instance()->DrawEnd();

		// �X�V������̎��Ԍv��
		float updateTime;
		mainWorld.Timer.GetPassTime(&updateTime);

		// �t���[�����[�g���� (�Ⴆ�΁A60FPS��ڎw���ꍇ)
		if (updateTime < FRAME_TIME) {
			DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - updateTime) * 1000);
			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
		}

		// deltaTime�̌v�Z
		mainWorld.Timer.GetPassTime(&mainWorld.deltaTime);
		// FPS�̌v�Z
		mainWorld.fps = 1.0f / mainWorld.deltaTime;
	}



	/**
	 * @brief �G���W���I������
	 */
	static void Exit() {
		MyApp::Instance()->ReleaseData();
	}

};

class TestObject : public Object

{
private:
	Timer TimeHandle;
	Timer TimeHandle2;
public:
	TestObject() {
		TimeHandle.Bind(0.5,this,&TestObject::Func,true);
		TimeHandle2.Bind(2.0,this,&TestObject::Func2,true);
	}

private:
	void Func()
	{
		std::cout << "Hello World" << std::endl;
	}
	void Func2()
	{
		std::cout << "By World" << std::endl;
	}

};


int main() {
	setlocale(LC_ALL, "Japanese");		// ���{��Ƀ��P�[����ݒ�.

#ifdef MEMORY_LEAK
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	for (int i = 0; i < 10; i++) {
		std::cout << Math::RandReal(0,10) << std::endl;
	}
	
	Engine::Init();

	ShowWindow(MyApp::Instance()->GetHWND(), SW_SHOWNORMAL);	// �쐬�����E�B���h�E��\������.

	// �C�x���g���[�v.
	// �u���b�N�^�֐�GetMessage�ł͂Ȃ��m���u���b�N�^�֐���PeekMessage���g��.
	MSG msg;
	bool flag = true;
	while (flag) {
		// ���b�Z�[�W�����邩�ǂ����m�F����.
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			// ���b�Z�[�W������̂ŏ�������.
			if (GetMessage(&msg, NULL, 0, 0) != 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				flag = 0;
			}
		}
		else {

			Engine::Tick();
		}
		// Sleep�ȂǍs���Ă��Ȃ����ADrawData�֐�����pDevice->Present��.
		// ��ʍX�V�҂����s���̂ŁA���ʓI��VSync���ƂɃC�x���g���[�v�����.
	}

	Engine::Exit();

#ifdef MEMORY_LEAK
	_CrtDumpMemoryLeaks();		// ���������[�N�����o����.
#endif
	return 0;
}