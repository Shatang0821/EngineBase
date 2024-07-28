#include "stdafx.h"
#include "CollisionManager.h"

void CollisionManager::Initialize()
{
	//当たり判定ハッシュテーブルの初期化
	
}

bool CollisionManager::FindMapping(CollisionType type1, CollisionType type2)
{
	int result = int(type1) * int(type1) + int(type2) * int(type2);
	return collisionMap.find(result) != collisionMap.end();
}

void CollisionManager::AddMapping(CollisionType type1, CollisionType type2)
{
	int result = int(type1) * int(type1) + int(type2) * int(type2);
	collisionMap.insert(result);
}

