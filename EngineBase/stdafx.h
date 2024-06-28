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
#include <vector>
#include <tchar.h>
#include <locale.h>
#include <assert.h>
#include <d3d9.h>		// Direct3D9 (DirectX9 Graphics)に必要.
#include <d3dx9core.h>	// DirectX スプライトに必要.
#include <dsound.h>	// DirectSoundに必要.

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
#define WIDTH (512)	// 幅.
#define HEIGHT (512)	// 高さ.

#endif // !_STDAFX_H_

