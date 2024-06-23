/**
 * @file GameStatics.h
 * @brief Worldを操作するクラス
 *

 * @author サトウ
 * @date 2024/06/22
 */
#ifndef _GAMESTATICS_H_
#define _GAMESTATICS_H_

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

	template<typename T>
	static T* CreateObject(Vector2 pos = Vector2::Zero());
};

template<typename T>
inline T* GameStatics::CreateObject(Vector2 pos)
{
	T* pObj = new T();
	//派生クラスを基底クラスにキャストするだけからstatic_castを使う
	if (pObj && static_cast<Object*>(pObj)) {
		mainWorld.GameObjects.insert(pObj);
		pObj->SetLocalPosition(pos);
		return pObj;
	}
	//失敗したらnullを返す
	return nullptr;
}

#endif // !_GAMESTATICS_H_


