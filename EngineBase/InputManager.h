#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

// dinput.h�̃C���N���[�h�̑O�ɂǂ̃o�[�W�������g�������`����K�v������.
#define DIRECTINPUT_VERSION 0x0800// ���ꂪ�Ȃ��ƃr���h���Ɍx�����ł�.
#include <dinput.h>
#include "Singleton.h"

constexpr int KEYBUF_SIZE = 256;// �L�[�{�[�h���͏��𓾂邽�߂̃o�b�t�@�T�C�Y.

// ID�̏��Ԃ�DX���C�u�����̃r�b�g�z����Q�l�ɂ��Ă���.
enum E_MOUSE_BTN_ID
{
	MOUSE_BTN_L,
	MOUSE_BTN_R,
	MOUSE_BTN_M,

	MOUSE_BTN_COUNT,
};
// IsPushMouse�֐��Ɏg��btn�̒l���r�b�g���Z�Ŏw��.
#define MOUSE_BTN_BIT_L	(1 << MOUSE_BTN_L)
#define MOUSE_BTN_BIT_R	(1 << MOUSE_BTN_R)
#define MOUSE_BTN_BIT_M	(1 << MOUSE_BTN_M)
typedef int MOUSE_BTN_BIT;

struct MYMOUSEINFO
{
	int click;		// �N���b�N���.	MOUSE_BTN_BIT_L | MOUSE_BTN_BIT_R | MOUSE_BTN_BIT_M
	int x;			// �����W.		
	int y;			// �����W.
};


enum E_JOY_CON_ID
{
	JOY_CON_0,
	JOY_CON_1,

	JOY_CON_COUNT,			// �Q�[���Ŏg���R���g���[���̍ő吔.
	JOY_CON_INVALID = -1,
	JOY_CON_BEGIN,
};

/*
	DIJOYSTATE�\���̂ɓ���f�[�^�̏ڍ�
		lX		���X�e�B�b�N�����ɓ|����-255�܂ŁA�E�ɓ|����+255�܂�
		lY		���X�e�B�b�N����ɓ|����-255�܂ŁA���ɓ|����+255�܂�
		lZ		(R2|ZR)��-255�܂� (L2|ZL)��+255�܂�
		lRx		�E�X�e�B�b�N�����ɓ|����-255�܂ŁA�E�ɓ|����+255�܂�
		lRy		�E�X�e�B�b�N����ɓ|����-255�܂ŁA���ɓ|����+255�܂�

		rgdwPOV		������Ă��Ȃ��Ƃ�0xffffffff
			[0]	�\���{�^�����0�A�E��9000�A����18000�A����27000�A

		rgbButtons	[0]�`[9] ������Ă��Ȃ��Ƃ�0�A������Ă���Ƃ�128
			[0]	�~�{�^���b�`�{�^��
			[1]	�Z�{�^���b�a�{�^��
			[2]	���{�^���b�w�{�^��
			[3]	���{�^���b�x�{�^��
			[4]	L1�{�^���b�k�{�^��
			[5]	R1�{�^���b�q�{�^��
			[6]	�V�F�A�{�^��
			[7]	�I�v�V�����{�^��
			[8]	���X�e�B�b�N��������
			[9]	�E�X�e�B�b�N��������
*/

// �\���ȊO�̃{�^��(�l�[�~���O��XBOX�R���g���[���ɏ���).
enum E_JOY_BTN_LAW_ID
{
	JOY_BTN_LAW_A,		// 0 : �`�{�^��.
	JOY_BTN_LAW_B,		// 1 : �a�{�^��.
	JOY_BTN_LAW_X,		// 2 : �w�{�^��.
	JOY_BTN_LAW_Y,		// 3 : �x�{�^��.
	JOY_BTN_LAW_L,		// 4 : �k�{�^��.
	JOY_BTN_LAW_R,		// 5 : �q�{�^��.
	JOY_BTN_LAW_VW,		// 6 : view�{�^��.
	JOY_BTN_LAW_MU,		// 7 : menu�{�^��.
	JOY_BTN_LAW_L3,		// 8 : ���X�e�B�b�N��������.
	JOY_BTN_LAW_R3,		// 9 : �E�X�e�B�b�N��������.

	JOY_BTN_LAW_COUNT,
	JOY_BTN_LAW_INVALID = -1,
	JOY_BTN_LAW_BEGIN,
};
#define	IS_VALID_BTN_LAW_ID(id)	((JOY_BTN_LAW_BEGIN <= id) && (id < JOY_BTN_LAW_COUNT))

// ID�̏��Ԃ�DX���C�u�����̃r�b�g�z����Q�l�ɂ��Ă���.
enum E_JOY_BTN_ID
{
	JOY_BTN_DN,		//  0 : �\���L�[��.
	JOY_BTN_LT,		//  1 : �\���L�[��.
	JOY_BTN_RT,		//  2 : �\���L�[�E.
	JOY_BTN_UP,		//  3 : �\���L�[��.
	JOY_BTN_A,		//  4 :	�`�{�^��.
	JOY_BTN_B,		//  5 : �a�{�^��.
	JOY_BTN_X,		//  6 : �w�{�^��.
	JOY_BTN_Y,		//  7 : �x�{�^��.
	JOY_BTN_L,		//  8 : �k�{�^��.
	JOY_BTN_R,		//  9 : �q�{�^��.
	JOY_BTN_VW,		// 10 : view�{�^��.
	JOY_BTN_MU,		// 11 : menu�{�^��.
	JOY_BTN_L3,		// 12 : ���X�e�B�b�N��������.
	JOY_BTN_R3,		// 13 : �E�X�e�B�b�N��������.

	JOY_BTN_COUNT,
	JOY_BTN_BEGIN = 0,
};
#define	JOY_BTN_BIT_DN	(1 << JOY_BTN_DN)		// 0x00000001
#define	JOY_BTN_BIT_LT	(1 << JOY_BTN_LT)		// 0x00000002
#define	JOY_BTN_BIT_RT	(1 << JOY_BTN_RT)		// 0x00000004
#define	JOY_BTN_BIT_UP	(1 << JOY_BTN_UP)		// 0x00000008
#define	JOY_BTN_BIT_A	(1 << JOY_BTN_A)		// 0x00000010
#define	JOY_BTN_BIT_B	(1 << JOY_BTN_B)		// 0x00000020
#define	JOY_BTN_BIT_X	(1 << JOY_BTN_X)		// 0x00000040
#define	JOY_BTN_BIT_Y	(1 << JOY_BTN_Y)		// 0x00000080
#define	JOY_BTN_BIT_L	(1 << JOY_BTN_L)		// 0x00000100
#define	JOY_BTN_BIT_R	(1 << JOY_BTN_R)		// 0x00000200
#define	JOY_BTN_BIT_CR	(1 << JOY_BTN_VW)		// 0x00000400
#define	JOY_BTN_BIT_OP	(1 << JOY_BTN_MU)		// 0x00000800
#define	JOY_BTN_BIT_L3	(1 << JOY_BTN_L3)		// 0x00001000
#define	JOY_BTN_BIT_R3	(1 << JOY_BTN_R3)		// 0x00002000
typedef int JOY_BTN_BIT;

struct MYJOYINFO
{
	int button;		// �{�^�����.		MY_PAD_INP_DN | MY_PAD_INP_LT | ...
	int lx, ly;		// ���X�e�B�b�N���.
	int rx, ry;		// �E�X�e�B�b�N���.
};

class InputManager : public Singleton<InputManager>
{
	friend class Singleton<InputManager>;
protected:
	/**
	 * @brief �R���X�g���N�^
	 *
	 * �V���O���g���p�^�[�����ێ����邽�߂�protected�ɂ��Ă��܂��B
	 */
	InputManager();

	/**
	 * @brief �f�X�g���N�^
	 *
	 * �V���O���g���p�^�[�����ێ����邽�߂�protected�ɂ��Ă��܂��B
	 */
	~InputManager() { Release(); }
public:
	HRESULT InitInput(HINSTANCE, HWND);		// ���̓f�o�C�X�̏�����.
	void Release();							// ���\�[�X���.

	void UpdateInput(HWND);					// ���͏����X�V.

	// ���L�[�{�[�h�֘A.
	BOOL IsPushKey(BYTE code);				// �w��̃L�[��������Ă��邩?
	BOOL IsPushKeyOne(BYTE code);			// �w��̃L�[�������ꂽ�u�Ԃ�?

	// ���}�E�X�֘A.
	BOOL IsPushMouse(MOUSE_BTN_BIT);		// �}�E�X�́i���^���^�E�j�{�^����������Ă��邩?
	BOOL IsPushMouseOne(MOUSE_BTN_BIT);		// �}�E�X�́i���^���^�E�j�{�^���������ꂽ�u�Ԃ�?
	void GetMousePos(LONG* px, LONG* py);	// �}�E�X�ʒu�̎擾.

	// ���W���C�X�e�B�b�N�֘A.
	BOOL IsPushBtn(E_JOY_CON_ID, JOY_BTN_BIT);		// �{�^����������Ă��邩?
	BOOL IsPushBtnOne(E_JOY_CON_ID, JOY_BTN_BIT);	// �{�^���������ꂽ�u�Ԃ�?
	int GetStickLX(E_JOY_CON_ID);					// ���X�e�B�b�N�̍��E�����̌X���𓾂�.
	int GetStickLY(E_JOY_CON_ID);					// ���X�e�B�b�N�̑O������̌X���𓾂�.
	int GetStickRX(E_JOY_CON_ID);					// �E�X�e�B�b�N�̍��E�����̌X���𓾂�.
	int GetStickRY(E_JOY_CON_ID);					// �E�X�e�B�b�N�̑O������̌X���𓾂�.
	int GetJoyCnt() { return m_nJoyCnt; }				// �ڑ�����Ă���R���g���[���̐��𓾂�.

private:
	LPDIRECTINPUT8 m_pDInput;						// �_�C���N�g�C���v�b�g.
	LPDIRECTINPUTDEVICE8 m_pKeyboardDev;			// �L�[�{�[�h�f�o�C�X.
	LPDIRECTINPUTDEVICE8 m_pMouseDev;				// �}�E�X�f�o�C�X.
	LPDIRECTINPUTDEVICE8 m_pJoystickDev[JOY_CON_COUNT];// �W���C�X�e�B�b�N�f�o�C�X�i�Q�܂Ŏg����j.

	char		m_keyboardInfo[2][KEYBUF_SIZE];		// �L�[�{�[�h���i�Q�t���[�����j.
	MYMOUSEINFO	m_mouseInfo[2];						// �}�E�X���i�Q�t���[�����j.
	MYJOYINFO	m_joystickInfo[JOY_CON_COUNT][2];	// �W���C�X�e�B�b�N���i�Q�t���[�����j.
	int			m_nJoyCnt;
	int			m_nDioiCnt;

	static BOOL CALLBACK EnumDevObjCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE*, LPVOID);
};

#endif // !_INPUTMANAGER_H_



