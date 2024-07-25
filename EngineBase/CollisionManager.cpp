#include "stdafx.h"
#include "CollisionManager.h"

void CollisionManager::Initialize()
{
	//�����蔻��n�b�V���e�[�u���̏�����
	AddMapping("Player","Platform");	//�v���C���[�ƃv���b�g�t�H�[��
}

bool CollisionManager::FindMapping(const std::string& key1, const std::string& key2)
{
	//�L�[�����݂��邩�ǂ����𒲂ׂ�
	auto it = collisionMap.find(key1);
	if(it != collisionMap.end()) {
		//�L�[�����݂���ꍇ�A���̃L�[�ɑΉ�����l��key2���܂܂�Ă��邩�ǂ����𒲂ׂ�
		return it->second.find(key2) != it->second.end();
	}

	return false;
}

void CollisionManager::AddMapping(const std::string& key1, const std::string& key2)
{
	//�L�[�����݂��Ȃ��ꍇ�A�V�����L�[��ǉ�
	if(collisionMap.find(key1) == collisionMap.end()) {
		collisionMap.insert({ key1,std::unordered_set<std::string>()});
	}
	if(collisionMap.find(key2) == collisionMap.end()) {
		collisionMap.insert({ key2,std::unordered_set<std::string>() });
	}

	collisionMap[key1].insert(key2);
	collisionMap[key2].insert(key1);
}
