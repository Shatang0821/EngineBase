/**
 * @file GameStatics.h
 * @brief World�𑀍삷��N���X
 *

 * @author �T�g�E
 * @date 2024/06/22
 */
#ifndef _GAMESTATICS_H_
#define _GAMESTATICS_H_

#include "World.h"

 /**
   * @class GameStatics
   * @brief World�𑀍삷��N���X
   *
   * @details ���̃N���X�́A
   * Engine���ɂ���World�𑀍삷��N���X
   *
   */
class GameStatics final
{
public:
	/**
	 * @brief GameInstance���擾����
	 */
	static GameInstance* GetGameInstance();

	/**
	 * @brief Controller���擾����
	 */
	static Controller* GetController();

	template<typename T>
	static T* CreateObject(Vector2 pos = Vector2::Zero());
};

template<typename T>
inline T* GameStatics::CreateObject(Vector2 pos)
{
	T* pObj = new T();
	//�h���N���X�����N���X�ɃL���X�g���邾������static_cast���g��
	if (pObj && static_cast<Object*>(pObj)) {
		mainWorld.GameObjects.insert(pObj);
		pObj->SetLocalPosition(pos);
		return pObj;
	}
	//���s������null��Ԃ�
	return nullptr;
}

#endif // !_GAMESTATICS_H_


