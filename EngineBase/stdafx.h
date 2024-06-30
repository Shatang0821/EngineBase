/**
 * @file stdafx.h
 * @brief プリコンパイルヘッダーを使用するためのファイル
 *
 * このファイルは、プリコンパイルヘッダー（PCH）を使用するために必要なヘッダーファイルを含めるためのものです。
 * プリコンパイルヘッダーを使用することで、コンパイル時間を短縮することができます。
 *
 * @note このファイルをプリコンパイルヘッダーとしてプロジェクト設定で指定してください。
 *
 * @date 2024/06/28
 * @author サトウ
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_


 // 標準ヘッダファイルのインクルード.
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
#include <d3d9.h>		// Direct3D9 (DirectX9 Graphics)に必要.
#include <d3dx9core.h>	// DirectX スプライトに必要.
#include <dsound.h>	// DirectSoundに必要.

#include "Singleton.h"
#include "Transform.h"
#include "Math.h"
#include "Vector2.h"

#define DIRECTINPUT_VERSION 0x0800// これがないとビルド時に警告が出る.
#include <dinput.h>	// DirectInputに必要.


#define MEMORY_LEAK
#ifdef MEMORY_LEAK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


// 汎用的な定義など.
#define WIDTH (1920)	// 幅.
#define HEIGHT (1080)	// 高さ.

#define TARGET_FPS 60					// fps
#define FRAME_TIME (1.0f / TARGET_FPS)	// フレームタイム
#define FIXED_DELTA_TIME 0.02f			// 固定間隔タイム

#endif // !_STDAFX_H_

