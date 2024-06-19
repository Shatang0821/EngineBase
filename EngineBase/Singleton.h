/**
 * @file Singleton.h
 * @brief シングルトンのテンプレートとなる
 *
 * このファイルには、シングルトンパターンを実装するための基底テンプレートクラスが定義されています。
 *
 * @author サトウ
 * @date 2024/06/19
 */

#ifndef _MANAGER_H_
#define _MANAGER_H_

 /**
  * @class Singleton
  * @brief シングルトンクラスの基底テンプレート
  *
  * このクラスは、シングルトンパターンを実装するための基底テンプレートクラスです。
  *
  * @tparam T 管理するクラスの型
  */
template <typename T>
class Singleton
{
public:
	/**
	 * @brief インスタンスを取得する
	 *
	 * この関数は、シングルトンインスタンスを取得します。
	 * インスタンスが存在しない場合は、新しく作成されます。
	 *
	 * @return T* シングルトンインスタンスへのポインタ
	 */
	static T* instance() {
		if (!manager)
			manager = new T();
		return manager;
	}
private:
	//! 管理するシングルトンインスタンスを指します。
	static T* manager;
protected:
    /**
     * @brief コンストラクタ
     *
     * シングルトンインスタンスの生成を防ぐためにprotectedにしています。
     */
    Manager() = default;

    /**
     * @brief デストラクタ
     *
     * シングルトンインスタンスの破棄を防ぐためにprotectedにしています。
     */
    ~Manager() = default;

    /**
     * @brief コピーコンストラクタ（削除）
     *
     * シングルトンパターンを維持するために削除しています。
     */
    Manager(const Manager&) = delete;

    /**
     * @brief 代入演算子（削除）
     *
     * シングルトンパターンを維持するために削除しています。
     *
     * @return Manager& 自身への参照
     */
    Manager& operator=(const Manager&) = delete;
};

template <typename T>
T* Singleton<T>::manager = nullptr;
#endif // !_MANAGER_H_



