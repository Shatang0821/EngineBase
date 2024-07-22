/**
 * @file GameStatics.h
 * @brief World�𑀍삷��N���X
 *

 * @author �T�g�E
 * @date 2024/06/22
 */
#ifndef _GAMESTATICS_H_
#define _GAMESTATICS_H_

#include "GameInstance.h"
#include "Vector2.h"
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

	/**
	 * @brief �w�肳�ꂽ�ʒu�ɐV�����I�u�W�F�N�g���쐬���܂��B
	 *
	 * ���̊֐��́A�w�肳�ꂽ�ʒu�ɐV�����I�u�W�F�N�g���쐬���A�Q�[�����[���h�ɒǉ����܂��B
	 * �I�u�W�F�N�g������ɍ쐬����A���N���X�̃|�C���^�ɃL���X�g�ł���ꍇ�A���̃I�u�W�F�N�g��Ԃ��܂��B
	 * ���s�����ꍇ�� nullptr ��Ԃ��܂��B
	 *
	 * @tparam T �쐬����I�u�W�F�N�g�̌^�B
	 * @param pos �I�u�W�F�N�g��z�u����ʒu�B
	 * @return T* �쐬���ꂽ�I�u�W�F�N�g�ւ̃|�C���^�B�쐬�Ɏ��s�����ꍇ�� nullptr�B
	 */
	template<typename T>
	static T* CreateObject(Vector2 pos = Vector2::Zero());

	/**
	 * @brief �w�肳�ꂽ�N���X�^�̃I�u�W�F�N�g��S�Č����ĕԂ��܂��B
	 *
	 * ���̊֐��́A�Q�[�����[���h���ɑ��݂���S�ẴI�u�W�F�N�g�̒�����w�肳�ꂽ�N���X�^�̃I�u�W�F�N�g�������A
	 * �������܂ރx�N�^�[��Ԃ��܂��B
	 *
	 * @tparam T ������I�u�W�F�N�g�̃N���X�^�B
	 * @return std::vector<T*> ���������I�u�W�F�N�g�̃|�C���^���܂ރx�N�^�[�B�I�u�W�F�N�g��������Ȃ��ꍇ�͋�̃x�N�^�[��Ԃ��܂��B
	 */
	template<typename T>
	static std::vector<T*>FindObjectsOfClass();
};

template<typename T>
inline T* GameStatics::CreateObject(Vector2 pos)
{
	T* pObj = new T();
	//�h���N���X�����N���X�ɃL���X�g���邾������static_cast���g��
	if (pObj && static_cast<Object*>(pObj)) {
		mainWorld.GameObjects.insert(pObj);
		pObj->BeginPlay();
		//pObj->SetLocalPosition(pos);
		return pObj;
	}
	//���s������null��Ԃ�
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


