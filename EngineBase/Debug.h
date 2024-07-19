/**
 * @file Debug.h
 * @brief 開発用のデバッグ機能を提供するクラス
 *
 * このファイルには、開発用のデバッグ機能を提供するDebugクラスが定義されています。
 *
 * @date 2024/07/19
 * @author サトウ
 */


#ifndef _DEBUG_H_
#define _DEBUG_H_


struct Vertex
{
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

/**
 * @class Debug
 * @brief 開発用のデバッグ機能を提供するクラス
 *
 * Debugクラスは、開発用のデバッグ機能を提供します。
 * 主に、線や四角形、円などの図形を描画するためのメソッドが実装されています。
 */
class Debug
{
public:
	
	/**
	 * @brief デバッグ用の線を描画します
	 */
	static void DrawLine(Vector2 start, Vector2 end, D3DCOLOR color);
	/**
	 * @brief デバッグ用の四角形を描画します
	 */
	static void DrawBox(Vector2 pos, Vector2 size, D3DCOLOR color);
	/**
	 * @brief デバッグ用の円を描画します
	 */
	static void DrawCircle(Vector2 pos, float radius, int segments, D3DCOLOR color);
};


#endif // !_DEBUG_H_