/**
 * @file stdafx.h
 * @brief �v���R���p�C���w�b�_�[���g�p���邽�߂̃t�@�C��
 *
 * ���̃t�@�C���́A�v���R���p�C���w�b�_�[�iPCH�j���g�p���邽�߂ɕK�v�ȃw�b�_�[�t�@�C�����܂߂邽�߂̂��̂ł��B
 * �v���R���p�C���w�b�_�[���g�p���邱�ƂŁA�R���p�C�����Ԃ�Z�k���邱�Ƃ��ł��܂��B
 *
 * @note ���̃t�@�C�����v���R���p�C���w�b�_�[�Ƃ��ăv���W�F�N�g�ݒ�Ŏw�肵�Ă��������B
 *
 * @date 2024/06/28
 * @author �T�g�E
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_


 // �W���w�b�_�t�@�C���̃C���N���[�h.
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <functional>
#include <vector>
#include <chrono>
#include <map>
#include <stack>
#include <set>
#include <string>
#include <algorithm>
#include <tchar.h>
#include <locale.h>
#include <assert.h>
#include <d3d9.h>		// Direct3D9 (DirectX9 Graphics)�ɕK�v.
#include <d3dx9core.h>	// DirectX �X�v���C�g�ɕK�v.
#include <dsound.h>	// DirectSound�ɕK�v.

#include "Singleton.h"
#include "Transform.h"
#include "Math.h"
#include "Vector2.h"

#define DIRECTINPUT_VERSION 0x0800// ���ꂪ�Ȃ��ƃr���h���Ɍx�����o��.
#include <dinput.h>	// DirectInput�ɕK�v.


#define MEMORY_LEAK
#ifdef MEMORY_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


// �ėp�I�Ȓ�`�Ȃ�.
#define WIDTH (1920)	// ��.
#define HEIGHT (1080)	// ����.

#define TARGET_FPS 60					// fps
#define FRAME_TIME (1.0f / TARGET_FPS)	// �t���[���^�C��
#define FIXED_DELTA_TIME 0.02f			// �Œ�Ԋu�^�C��

#endif // !_STDAFX_H_

