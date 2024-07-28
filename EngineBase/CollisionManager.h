/**
 * @file CollisionManager.h
 * @brief�@�����蔻����Ǘ�����N���X�̒�`
 *
 * ���̃t�@�C���ɂ́A�����蔻����Ǘ�����N���X�̒�`���܂܂�Ă��܂��B
 *
 * @date 2024/07/25
 * @autor �T�g�E
 */

#ifndef _COLLISIONMANAGER_H_

#include "Singleton.h"

enum class CollisionType : uint8_t
{
	Default,
	Player
};

class CollisionManager : public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;
private:
	std::unordered_set<int>collisionMap;
public:
	/**
	 * @brief Default�́A�S�ẴI�u�W�F�N�g�Ɠ����蔻����s��
	 *
	 */
	CollisionManager() { 
		collisionMap.insert({int(CollisionType::Default) * int(CollisionType::Default) + int(CollisionType::Default) * int(CollisionType::Default) });
	}

	void Initialize();

	/**
	 * @brief ���̊֐��́A�����蔻����s�����ǂ����𔻒肵�܂��B
	 *
	 * @param type1 �I�u�W�F�N�g1�̓����蔻��^�C�v
	 * @param type2 �I�u�W�F�N�g2�̓����蔻��^�C�v
	 *
	 * @return bool �����蔻����s���ꍇ��true�A�s��Ȃ��ꍇ��false
	 */
	bool FindMapping(CollisionType type1, CollisionType type2);

	/**
	 * @brief ���̊֐��́A�����蔻����s�����ǂ�����ݒ肵�܂��B
	 *
	 * @param type1 �I�u�W�F�N�g1�̓����蔻��^�C�v
	 * @param type2 �I�u�W�F�N�g2�̓����蔻��^�C�v
	 */
	void AddMapping(CollisionType type1, CollisionType type2);

};

#endif // !_COLLISIONMANAGER_H_



