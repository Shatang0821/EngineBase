#include "stdafx.h"
#include "myApp.h"
#include "StaticMesh.h"


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
		//Engine������

		//���[���h������
		mainWorld.currentLevel = new Level;
		mainWorld.gameInstance = new GameInstance;
	}

	/**
	 * @brief �G���W���X�V����
	 */
	static void Tick()
	{
		mainWorld.Input();
		mainWorld.Update(0.016f);
		mainWorld.Render();
	}

	/**
	 * @brief �G���W���I������
	 */
	static void Exit() {

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

	Engine::Init();

	TestObject testObj;
	ImageInterface test;
	std::cout << test.GetTransprancy() << std::endl;
	test.SetTransprancy(0.5);
	std::cout << test.GetTransprancy() << std::endl;

	MyApp* pApp = MyApp::Instance();
	if (pApp->InitApp()) {
		pApp->MainLoop();
	}
	pApp->ReleaseData();

#ifdef MEMORY_LEAK
	_CrtDumpMemoryLeaks();		// ���������[�N�����o����.
#endif
	//while (true)
	//{
	//	Engine::Tick();
	//	
	//}
	return 0;
}