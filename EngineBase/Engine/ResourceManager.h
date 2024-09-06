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
	Tex_Player_Idle,	//プレイヤー仮
	Tex_Player_Run,		//プレイヤー仮
	Tex_Player_Jump,	//プレイヤー仮
	Tex_Player_Fall,	//プレイヤー仮
};

//アニメーションリソース
struct AnimationResource
{
	//アトラス
	std::vector<MyTexture*> texs;
	//アニメーションのフレーム数
	int num;
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
private:
	//! 画像リソースのプール
	std::unordered_map<ResID, MyTexture*>imagePool;
	std::unordered_map<ResID, AnimationResource>animPool;
	/**
	 * @brief １枚画像リソースを読み込む
	 *
	 * 指定されたリソースIDとファイルパスに基づいて、画像リソースを読み込みます。
	 *
	 * @param pDev Direct3Dデバイス
	 * @param id リソースID
	 * @param pFname リソースファイルのパス
	 */
	bool LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname);

	/**
	 * @brief 複数枚画像リソースを読み込む
	 *
	 * 指定されたリソースIDとファイルパスに基づいて、画像リソースを読み込みます。
	 *
	 * @param pDev Direct3Dデバイス
	 * @param id リソースID
	 * @param pFname リソースファイルのパス.pngを書かない
	 * @param num 画像の枚数
	 */
	bool LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname,int num);

	/**
	 * @brief スプライトシート画像リソースを読み込む
	 *
	 * 指定されたリソースIDとファイルパスに基づいて、画像リソースを読み込みます。
	 *
	 * @param pDev Direct3Dデバイス
	 * @param id リソースID
	 * @param pFname リソースファイルのパス
	 * @param num 画像の枚数
	 * @param row 画像の行数
	 * @param col 画像の列数
	 * @param texWidth 画像の幅
	 * @param texHeight 画像の高さ
	 */
	bool LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname, int num, int row, int col, int texWidth, int texHeight);
	
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

public:
	/**
	 * @brief リソースマネージャの初期化
	 *
	 * 必要なリソースをすべて初期化し、読み込みます。
	 * 
	 * @return 成功した場合はtrue、失敗した場合はfalseを返します。
	 */
	bool Initalize();
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

	/**
	 * @brief 指定されたリソースIDに対応するアニメーションリソースを取得する
	 *
	 * 指定されたリソースIDに対応するアニメーションリソースを取得します。
	 * リソースが存在しない場合はnullptrを返します。
	 *
	 * @param id リソースID
	 * @return 指定されたリソースIDに対応するアニメーションリソース
	 */
	AnimationResource FetchAnim(ResID id);
};

#endif // !_RESOURCEMANAGER_H_


