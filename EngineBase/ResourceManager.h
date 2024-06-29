/**
 * @file ResourceManager.h
 * @brief リソース管理クラスの定義
 *
 * このファイルには、ResourceManagerクラスが定義されています。
 * ResourceManagerクラスは、ゲーム内で使用するリソース（画像など）を管理します。
 * 具体的には、リソースの読み込み、初期化、アクセスを行います。
 *
 * @date 2024/06/28
 * @author サトウ
 */
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "Singleton.h"
#include "MyTexture.h"
 /**
  * @enum ResID
  * @brief リソースIDを表す列挙型
  *
  * ゲーム内で使用するリソースを一意に識別するためのIDを定義します。
  */
enum class ResID
{
	Tex_Bullet,//仮
};

/**
 * @class ResourceManager
 * @brief リソース管理クラス
 *
 * このクラスは、ゲーム内で使用するリソースを管理します。
 * 具体的には、リソースの読み込み、初期化、アクセスを行います。
 */
class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
protected:
	/**
	 * @brief コンストラクタ
	 *
	 * シングルトンパターンを維持するためにprotectedにしています。
	 */
	ResourceManager() {};
	/**
	 * @brief デストラクタ
	 *
	 * シングルトンパターンを維持するためにprotectedにしています。
	 */
	~ResourceManager() {};
private:
	//! 画像リソースのプール
	std::map<ResID, MyTexture*>imagePool;
	/**
	 * @brief リソースを読み込む
	 *
	 * 指定されたリソースIDとファイルパスに基づいて、画像リソースを読み込みます。
	 *
	 * @param id リソースID
	 * @param pFname リソースファイルのパス
	 */

	void LoadTex(IDirect3DDevice9* pDev,ResID id,const TCHAR* pFname);
public:
	/**
	 * @brief リソースマネージャの初期化
	 *
	 * 必要なリソースをすべて初期化し、読み込みます。
	 */
	void Initalize();
	/**
	 * @brief 指定されたリソースIDに対応するテクスチャを取得する
	 *
	 * 指定されたリソースIDに対応するMyTextureオブジェクトを取得します。
	 * リソースが存在しない場合はnullptrを返します。
	 *
	 * @param id リソースID
	 * @return 指定されたリソースIDに対応するMyTextureオブジェクトのポインタ
	 */
	MyTexture* Fetch(ResID id);
};

#endif // !_RESOURCEMANAGER_H_


