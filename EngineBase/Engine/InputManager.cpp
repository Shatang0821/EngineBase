#include "stdafx.h"
#include "InputManager.h"

constexpr int DI_DEVOBJ_CNT = 64;

// OSが認識しているジョイスティックを列挙し、２つまで使えるようにする.
BOOL CALLBACK InputManager::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID*/* pContext*/)
{
	InputManager* pInp = Instance();

	// 列挙されたジョイスティックのデバイスを取得.
	HRESULT hr = pInp->m_pDInput->CreateDevice(pdidInstance->guidInstance, &pInp->m_pJoystickDev[pInp->m_nJoyCnt], NULL);
	if (FAILED(hr)) { return DIENUM_CONTINUE; }
	pInp->m_nJoyCnt++;

	// ジョイコンの列挙はゲームで使う数まで列挙したら終わる.
	return ((pInp->m_nJoyCnt >= JOY_CON_COUNT) ? DIENUM_STOP : DIENUM_CONTINUE);
	//	return DIENUM_STOP;// １つしか使わない場合は↑の代わりにこちらで.
}

BOOL CALLBACK InputManager::EnumDevObjCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	InputManager* pInp = Instance();

	assert(pInp->m_nDioiCnt < DI_DEVOBJ_CNT);
	if (pInp->m_nDioiCnt < DI_DEVOBJ_CNT) {
		LPCDIDEVICEOBJECTINSTANCE pDst = (LPCDIDEVICEOBJECTINSTANCE)pvRef;
		pDst += pInp->m_nDioiCnt;
		memcpy((void*)pDst, lpddoi, sizeof(DIDEVICEOBJECTINSTANCE));
		pInp->m_nDioiCnt++;
	}

	// 列挙は全て終われば自動的に終了するので、列挙し続ける.
	return DIENUM_CONTINUE;
}

InputManager::InputManager()
	: m_pDInput(NULL)
	, m_pKeyboardDev(NULL)
	, m_pMouseDev(NULL)
	, m_nJoyCnt(0)
	, m_nDioiCnt(0)
{
	memset(m_pJoystickDev, NULL, sizeof(m_pJoystickDev));
	memset(m_keyboardInfo, NULL, sizeof(m_keyboardInfo));
	memset(m_mouseInfo, NULL, sizeof(m_mouseInfo));
	memset(m_joystickInfo, NULL, sizeof(m_joystickInfo));
}

HRESULT InputManager::InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = D3D_OK;

	assert(m_pDInput == NULL);
	if (m_pDInput != NULL) {
		return D3D_OK;// 初期化済み.
	}

	// DirectInputの初期化.
	hr = DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDInput,
		NULL
	);
	if (FAILED(hr)) return hr;

	// キーボード.
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDev, NULL);
	if (SUCCEEDED(hr))
	{
		// デバイスのフォーマット設定.
		hr = m_pKeyboardDev->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) return hr;

		// 協調レベル.
		hr = m_pKeyboardDev->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) return hr;

		hr = m_pKeyboardDev->Acquire();
		if (FAILED(hr)) return hr;

		// ポーリング開始.
		hr = m_pKeyboardDev->Poll();
		if (FAILED(hr)) return hr;
	}

	// マウス.
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pMouseDev, NULL);
	if (SUCCEEDED(hr))
	{
		// デバイスのフォーマット設定.
		hr = m_pMouseDev->SetDataFormat(&c_dfDIMouse);
		if (FAILED(hr)) return hr;

		// 協調レベル.
		hr = m_pMouseDev->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) return hr;

		hr = m_pMouseDev->Acquire();
		if (FAILED(hr)) return hr;

		// ポーリング開始.
		hr = m_pMouseDev->Poll();
		if (FAILED(hr)) return hr;
	}

	// ジョイスティック.
	// 接続されているゲームコントローラ（ジョイスティック）を列挙する.
	m_nJoyCnt = 0;// 念のため０クリア.
	m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);

	// 列挙したジョイスティックの数だけループする.
	for (int joy = 0; joy < m_nJoyCnt; joy++) {
		// デバイスのフォーマット設定.
		hr = m_pJoystickDev[joy]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) return hr;

		// 協調レベル.
		hr = m_pJoystickDev[joy]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) return hr;

		// 軸モードの設定.
		DIPROPDWORD diPropData;
		diPropData.diph.dwSize = sizeof(DIPROPDWORD);
		diPropData.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diPropData.diph.dwHow = DIPH_DEVICE;
		diPropData.diph.dwObj = 0;
		diPropData.dwData = DIPROPAXISMODE_ABS;
		hr = m_pJoystickDev[joy]->SetProperty(DIPROP_AXISMODE, &diPropData.diph);
		if (FAILED(hr)) return hr;

		// 軸の値の設定.
		m_nDioiCnt = 0;
		DIDEVICEOBJECTINSTANCE dioiDataArr[DI_DEVOBJ_CNT];// 
		m_pJoystickDev[joy]->EnumObjects(EnumDevObjCallback, dioiDataArr, DIDFT_ALL);
		for (int obj = 0; obj < m_nDioiCnt; obj++) {
			DIPROPRANGE diPropRange;
			diPropRange.diph.dwSize = sizeof(DIPROPRANGE);// 使用される構造体のサイズ.
			diPropRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);// DIPROPHEADER構造体のサイズ.
			diPropRange.diph.dwHow = DIPH_BYID;// 対象（ここでは軸）.
			diPropRange.diph.dwObj = dioiDataArr[obj].dwType;// 対象となる軸.
			diPropRange.lMin = -255;// 最小値.
			diPropRange.lMax = +255;// 最大値.

			// 設定.
			m_pJoystickDev[joy]->SetProperty(DIPROP_RANGE, &diPropRange.diph);
		}

		hr = m_pJoystickDev[joy]->Acquire();
		if (FAILED(hr)) return hr;

		// ポーリング開始.
		hr = m_pJoystickDev[joy]->Poll();
		if (FAILED(hr)) return hr;
	}

	return D3D_OK;
}

void InputManager::Release()
{
	for (int joy = m_nJoyCnt - 1; joy >= 0; joy--) {
		if (m_pJoystickDev[joy]) {
			m_pJoystickDev[joy]->Unacquire();
			m_pJoystickDev[joy]->Release();
			m_pJoystickDev[joy] = NULL;
		}
	}
	if (m_pMouseDev) {
		m_pMouseDev->Unacquire();
		m_pMouseDev->Release();
		m_pMouseDev = NULL;
	}
	if (m_pKeyboardDev) {
		m_pKeyboardDev->Unacquire();
		m_pKeyboardDev->Release();
		m_pKeyboardDev = NULL;
	}

	if (m_pDInput) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

void InputManager::UpdateInput(HWND hWnd)
{
	HRESULT ret = 0;

	// 前フレームの入力情報をインデックス１に保存.
	{
		memcpy(&m_keyboardInfo[1][0], &m_keyboardInfo[0][0], KEYBUF_SIZE);
		m_mouseInfo[1] = m_mouseInfo[0];
		for (int joy = 0; joy < m_nJoyCnt; joy++) {
			m_joystickInfo[joy][1] = m_joystickInfo[joy][0];
		}
	}

	// キーボード情報取得.
	if (m_pKeyboardDev) {
		ret = m_pKeyboardDev->GetDeviceState(KEYBUF_SIZE, m_keyboardInfo[0]);
		if (FAILED(ret)) {
			m_pKeyboardDev->Acquire();
			m_pKeyboardDev->GetDeviceState(KEYBUF_SIZE, m_keyboardInfo[0]);
		}
	}

	// マウスクリック情報取得.
	m_mouseInfo[0] = { 0 };
	if (m_pMouseDev) {
		DIMOUSESTATE info;
		ret = m_pMouseDev->GetDeviceState(sizeof(DIMOUSESTATE), &info);
		if (FAILED(ret)) {
			m_pMouseDev->Acquire();
			ret = m_pMouseDev->GetDeviceState(sizeof(DIMOUSESTATE), &info);
		}
		if (SUCCEEDED(ret)) {
			for (int id = 0; id < MOUSE_BTN_COUNT; id++) {
				if (info.rgbButtons[id] & 0x80) {
					m_mouseInfo[0].click |= (1 << id);
				}
			}
		}
	}

	// マウス座標の取得はWINAPIで行う.
	POINT pt = { 0 };
	if (GetCursorPos(&pt)) {
		// ↑はスクリーン座標系なので、クライアント座標系に変換する↓.
		ScreenToClient(hWnd, &pt);
		m_mouseInfo[0].x = pt.x;
		m_mouseInfo[0].y = pt.y;
	}

	// ジョイスティック情報取得.
	for (int joy = 0; joy < m_nJoyCnt; joy++) {
		m_joystickInfo[joy][0] = { 0 };
		if (m_pJoystickDev[joy]) {
			DIJOYSTATE state = { 0 };
			ret = m_pJoystickDev[joy]->GetDeviceState(sizeof(DIJOYSTATE), &state);
			if (FAILED(ret)) {
				m_pJoystickDev[joy]->Acquire();
				ret = m_pJoystickDev[joy]->GetDeviceState(sizeof(DIJOYSTATE), &state);
				if (FAILED(ret)) {
					printf("Joystick入力情報取得エラー発生中...\n");
				}
			}
			if (SUCCEEDED(ret)) {
				for (int id = JOY_BTN_LAW_BEGIN; id < JOY_BTN_LAW_COUNT; id++) {
					if (state.rgbButtons[id] != 0) {
						m_joystickInfo[joy][0].button |= (1 << (id + JOY_BTN_A));
					}
				}

				// 入力があればinputには0以上36000未満の値が入る.
				INT input = state.rgdwPOV[0];
				if (input >= 0) {
					//					input /= 4500;// 45度単位にする.(0〜7)
					switch (input) {
					case 0 * 4500: m_joystickInfo[joy][0].button |= (JOY_BTN_BIT_UP);					break;
					case 1 * 4500: m_joystickInfo[joy][0].button |= (JOY_BTN_BIT_UP | JOY_BTN_BIT_RT);	break;
					case 2 * 4500: m_joystickInfo[joy][0].button |= JOY_BTN_BIT_RT;					break;
					case 3 * 4500: m_joystickInfo[joy][0].button |= (JOY_BTN_BIT_RT | JOY_BTN_BIT_DN);	break;
					case 4 * 4500: m_joystickInfo[joy][0].button |= JOY_BTN_BIT_DN;					break;
					case 5 * 4500: m_joystickInfo[joy][0].button |= (JOY_BTN_BIT_DN | JOY_BTN_BIT_LT);	break;
					case 6 * 4500: m_joystickInfo[joy][0].button |= JOY_BTN_BIT_LT;					break;
					case 7 * 4500: m_joystickInfo[joy][0].button |= (JOY_BTN_BIT_LT | JOY_BTN_BIT_UP);	break;
					}
					/*
										bit = (1 << input);
										if (input % 2) {
											// 奇数なら両サイドのビットも立てる(斜め押し).
											bit |= (1 << ((input+1)%8));
											bit |= (1 << ((input+7)%8));
										}
					*/
				}
				//printf("button = 0x%08X\n", m_joystickInfo[joy]->button);

				// スティック情報をメンバにコピー.
				m_joystickInfo[joy][0].lx = state.lX;
				m_joystickInfo[joy][0].ly = state.lY;
				m_joystickInfo[joy][0].rx = state.lRx;
				m_joystickInfo[joy][0].ry = state.lRy;
			}
		}
	}
}

BOOL InputManager::IsPushKey(BYTE code)
{
	return (m_keyboardInfo[0][code] & 0x80);
}

BOOL InputManager::IsPushKeyOne(BYTE code)
{
	return ((m_keyboardInfo[0][code] & 0x80) && !(m_keyboardInfo[1][code] & 0x80));
}

BOOL InputManager::IsPushMouse(MOUSE_BTN_BIT bit)
{
	return (m_mouseInfo[0].click & bit);
}

BOOL InputManager::IsPushMouseOne(MOUSE_BTN_BIT bit)
{
	return ((m_mouseInfo[0].click & bit) && !(m_mouseInfo[1].click & bit));
}

void InputManager::GetMousePos(LONG* px, LONG* py)
{
	*px = m_mouseInfo[0].x;
	*py = m_mouseInfo[0].y;
}

BOOL InputManager::IsPushBtn(E_JOY_CON_ID joy, JOY_BTN_BIT bit)
{
	return (m_joystickInfo[joy][0].button & bit);
}

BOOL InputManager::IsPushBtnOne(E_JOY_CON_ID joy, JOY_BTN_BIT bit)
{
	return (m_joystickInfo[joy][0].button & bit) && !(m_joystickInfo[joy][1].button & bit);
}

int InputManager::GetStickLX(E_JOY_CON_ID joy)
{
	return (m_joystickInfo[joy][0].lx);
}

int InputManager::GetStickLY(E_JOY_CON_ID joy)
{
	return (m_joystickInfo[joy][0].ly);
}

int InputManager::GetStickRX(E_JOY_CON_ID joy)
{
	return (m_joystickInfo[joy][0].rx);
}

int InputManager:: GetStickRY(E_JOY_CON_ID joy)
{
	return (m_joystickInfo[joy][0].ry);
}
