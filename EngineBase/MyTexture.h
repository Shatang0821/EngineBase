/**
 * @file myTexture.h
 * @brief テクスチャー管理クラス
 *
 * このファイルには、Direct3Dを使用してテクスチャを管理するための
 * MyTextureクラスが定義されています。テクスチャの読み込み、取得、
 * 破棄を簡単に行うためのインターフェースを提供します。
 *
 * @date 2024/06/28
 * @author サトウ
 */

#ifndef _MYTEXTURE_H_
#define _MYTEXTURE_H_


//! 管理する最大テクスチャ数
const int MAX_TEXTURE = 256;

/**
 * @class MyTexture
 * @brief テクスチャー管理クラス
 *
 * このクラスは、Direct3Dテクスチャを管理し、テクスチャの読み込み、
 * 取得、破棄を行います。シングルトンパターンを使用して複数のテクスチャ
 * を管理します。
 */
class MyTexture
{
private: 
	//! テクスチャ管理スタック
	static MyTexture* sm_pStack[MAX_TEXTURE];
	//! 管理するテクスチャの数
	static int sm_maxTexture;

protected:
	//! 管理するテクスチャ
	IDirect3DTexture9* m_pTex;
	//! テクスチャの幅
	int m_width;
	//! テクスチャの高さ
	int m_height;
private:
	/**
	* @brief コンストラクタ
	*
	* MyTextureクラスのインスタンスを初期化します。
	* テクスチャポインタm_pTexをNULLで初期化します。
	*/
	MyTexture() 
	: m_pTex(NULL)
	, m_width(0)
	, m_height(0)
	{
	}
	/**
	 * @brief デストラクタ
	 *
	 * MyTextureクラスのインスタンスを破棄します。
	 * 管理するテクスチャを解放します。
	 */
	virtual ~MyTexture()
	{
		if (m_pTex)
		{
			m_pTex->Release();
		}
	}
public:
	/**
	 * @brief テクスチャを取得する
	 *
	 * テクスチャポインタを返します。
	 *
	 * @return テクスチャポインタ
	 */
	IDirect3DTexture9* GetTexture()
	{
		return m_pTex;
	}

	/**
	 * @brief テクスチャの幅を取得する
	 *
	 * 幅を返します。
	 *
	 * @return 幅
	 */
	int GetWidth() const { return m_width; }
	/**
	 * @brief テクスチャの高さを取得する
	 *
	 * 高さを返します。
	 *
	 * @return 高さ
	 */
	int GetHeight() const { return m_height; }

	/**
	 * @brief テクスチャを読み込む
	 *
	 * MyTextureオブジェクトを作成し、指定されたファイルからテクスチャを読み込みます。
	 *
	 * @param pDev Direct3Dデバイス
	 * @param pFname テクスチャファイル名
	 * @return MyTextureオブジェクトのポインタ
	 */
	static MyTexture* LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname);

	/**
	 * @brief スプライトを作成する
	 *
	 * スプライトシートから指定された領域のスプライトを作成します。
	 *
	 * @param pDev Direct3Dデバイス
	 * @param pFname スプライトシートのファイル名
	 * @param u1 スプライトの左上のU座標
	 * @param v1 スプライトの左上のV座標
	 * @param u2 スプライトの右下のU座標
	 * @param v2 スプライトの右下のV座標
	 * @return MyTextureオブジェクトのポインタ
	 */
	static MyTexture* CreateSprite(IDirect3DDevice9* pDev, const TCHAR* pFname, float u1, float v1, float u2, float v2);

	/**
	 * @brief 全てのテクスチャを破棄する
	 *
	 * 読み込んだ全てのテクスチャを破棄します。
	 */
	static void ReleaseAll();
};

/**
 * @brief テクスチャを読み込むヘルパー関数
 *
 * 指定されたファイルからDirect3Dテクスチャを読み込みます。
 *
 * @param pDev Direct3Dデバイス
 * @param pFname テクスチャファイル名
 * @param ppTex 読み込んだテクスチャポインタへのポインタ
 * @return HRESULT 成功した場合はS_OK、失敗した場合はエラーコード
 */
HRESULT LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname, IDirect3DTexture9** ppTex);
#endif // !_MYTEXTURE_H_
