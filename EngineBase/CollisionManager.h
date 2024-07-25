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

class CollisionManager : public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;
private:
	// unordered_map�́A�����蔻�������I�u�W�F�N�g�̃^�C�v���L�[��
	// ���̃I�u�W�F�N�g�Ɣ��������I�u�W�F�N�g��l�Ŏ���
	std::unordered_map<std::string, std::unordered_set<std::string>>collisionMap;
public:
	/**
	 * @brief Default�́A�S�ẴI�u�W�F�N�g�Ɠ����蔻����s��
	 *
	 */
	CollisionManager() { collisionMap.insert({ "Default",std::unordered_set<std::string>{"Default"} }); }

	void Initialize();

	/**
	 * @brief ���̊֐��́A�L�[�����݂��邩�ǂ����𒲂ׂ܂��B
	 *
	 * @param key1 �L�[1
	 * @param key2 �L�[2
	 *
	 * @return �L�[�����݂��邩�ǂ���
	 */
	bool FindMapping(const std::string& key1, const std::string& key2);

	/**
	 * @brief ���̊֐��́A�L�[��ǉ����܂��B
	 *
	 * @param key1 �L�[1
	 * @param key2 �L�[2
	 *
	 */
	void AddMapping(const std::string& key1, const std::string& key2);

};

#endif // !_COLLISIONMANAGER_H_



