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

class CollisionManager : public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;
private:
	// unordered_mapは、当たり判定をするオブジェクトのタイプをキーで
	// そのオブジェクトと判定をするオブジェクトを値で持つ
	std::unordered_map<std::string, std::unordered_set<std::string>>collisionMap;
public:
	/**
	 * @brief Defaultは、全てのオブジェクトと当たり判定を行う
	 *
	 */
	CollisionManager() { collisionMap.insert({ "Default",std::unordered_set<std::string>{"Default"} }); }

	void Initialize();

	/**
	 * @brief この関数は、キーが存在するかどうかを調べます。
	 *
	 * @param key1 キー1
	 * @param key2 キー2
	 *
	 * @return キーが存在するかどうか
	 */
	bool FindMapping(const std::string& key1, const std::string& key2);

	/**
	 * @brief この関数は、キーを追加します。
	 *
	 * @param key1 キー1
	 * @param key2 キー2
	 *
	 */
	void AddMapping(const std::string& key1, const std::string& key2);

};

#endif // !_COLLISIONMANAGER_H_



