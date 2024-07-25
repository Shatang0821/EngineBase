#include "stdafx.h"
#include "CollisionManager.h"

void CollisionManager::Initialize()
{
	//当たり判定ハッシュテーブルの初期化
	AddMapping("Player","Platform");	//プレイヤーとプラットフォーム
}

bool CollisionManager::FindMapping(const std::string& key1, const std::string& key2)
{
	//キーが存在するかどうかを調べる
	auto it = collisionMap.find(key1);
	if(it != collisionMap.end()) {
		//キーが存在する場合、そのキーに対応する値にkey2が含まれているかどうかを調べる
		return it->second.find(key2) != it->second.end();
	}

	return false;
}

void CollisionManager::AddMapping(const std::string& key1, const std::string& key2)
{
	//キーが存在しない場合、新しいキーを追加
	if(collisionMap.find(key1) == collisionMap.end()) {
		collisionMap.insert({ key1,std::unordered_set<std::string>()});
	}
	if(collisionMap.find(key2) == collisionMap.end()) {
		collisionMap.insert({ key2,std::unordered_set<std::string>() });
	}

	collisionMap[key1].insert(key2);
	collisionMap[key2].insert(key1);
}
