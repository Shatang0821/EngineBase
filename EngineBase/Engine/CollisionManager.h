/**
 * @file CollisionManager.h
 * @brief　当たり判定を管理するクラスの定義
 *
 * このファイルには、当たり判定を管理するクラスの定義が含まれています。
 *
 * @date 2024/07/25
 * @autor サトウ
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
	 * @brief Defaultは、全てのオブジェクトと当たり判定を行う
	 *
	 */
	CollisionManager() { 
		collisionMap.insert({int(CollisionType::Default) * int(CollisionType::Default) + int(CollisionType::Default) * int(CollisionType::Default) });
	}

	void Initialize();

	/**
	 * @brief この関数は、当たり判定を行うかどうかを判定します。
	 *
	 * @param type1 オブジェクト1の当たり判定タイプ
	 * @param type2 オブジェクト2の当たり判定タイプ
	 *
	 * @return bool 当たり判定を行う場合はtrue、行わない場合はfalse
	 */
	bool FindMapping(CollisionType type1, CollisionType type2);

	/**
	 * @brief この関数は、当たり判定を行うかどうかを設定します。
	 *
	 * @param type1 オブジェクト1の当たり判定タイプ
	 * @param type2 オブジェクト2の当たり判定タイプ
	 */
	void AddMapping(CollisionType type1, CollisionType type2);

};

#endif // !_COLLISIONMANAGER_H_



