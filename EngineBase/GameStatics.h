/**
 * @file GameStatics.h
 * @brief Worldを操作するクラス
 *

 * @author サトウ
 * @date 2024/06/22
 */
#ifndef _GAMESTATICS_H_
#define _GAMESTATICS_H_

#include "GameInstance.h"
#include "Vector2.h"
#include "World.h"

 /**
   * @class GameStatics
   * @brief Worldを操作するクラス
   *
   * @details このクラスは、
   * Engine側にあるWorldを操作するクラス
   *
   */
class GameStatics final
{
public:
	/**
	 * @brief GameInstanceを取得する
	 */
	static GameInstance* GetGameInstance();

	/**
	 * @brief Controllerを取得する
	 */
	static Controller* GetController();

	/**
	 * @brief 指定された位置に新しいオブジェクトを作成します。
	 *
	 * この関数は、指定された位置に新しいオブジェクトを作成し、ゲームワールドに追加します。
	 * オブジェクトが正常に作成され、基底クラスのポインタにキャストできる場合、そのオブジェクトを返します。
	 * 失敗した場合は nullptr を返します。
	 *
	 * @tparam T 作成するオブジェクトの型。
	 * @param pos オブジェクトを配置する位置。
	 * @return T* 作成されたオブジェクトへのポインタ。作成に失敗した場合は nullptr。
	 */
	template<typename T>
	static T* CreateObject(Vector2 pos = Vector2::Zero());

	/**
	 * @brief 指定されたクラス型のオブジェクトを全て見つけて返します。
	 *
	 * この関数は、ゲームワールド内に存在する全てのオブジェクトの中から指定されたクラス型のオブジェクトを見つけ、
	 * それらを含むベクターを返します。
	 *
	 * @tparam T 見つけるオブジェクトのクラス型。
	 * @return std::vector<T*> 見つかったオブジェクトのポインタを含むベクター。オブジェクトが見つからない場合は空のベクターを返します。
	 */
	template<typename T>
	static std::vector<T*>FindObjectsOfClass();
};

template<typename T>
inline T* GameStatics::CreateObject(Vector2 pos)
{
	T* pObj = new T();
	//派生クラスを基底クラスにキャストするだけからstatic_castを使う
	if (pObj && static_cast<Object*>(pObj)) {
		mainWorld.GameObjects.insert(pObj);
		pObj->BeginPlay();
		//pObj->SetLocalPosition(pos);
		return pObj;
	}
	//失敗したらnullを返す
	return nullptr;
}

template<typename T>
inline std::vector<T*> GameStatics::FindObjectsOfClass()
{
	std::vector<T*> result;
	result.reserve(mainWorld.GameObjects.size());
	for (auto& obj : mainWorld.GameObjects) {
		if (T* pObj = static_cast<T*>(obj)) result.push_back(pObj);
	}
	return std::vector<T*>();
}

#endif // !_GAMESTATICS_H_


