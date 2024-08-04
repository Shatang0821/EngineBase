/**
 * @file Singleton.h
 * @brief シングルトンのテンプレートとなる
 *
 * このファイルには、シングルトンパターンを実装するための基底テンプレートクラスが定義されています。
 *
 * @author サトウ
 * @date 2024/06/19
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

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
     *
     * @return T& シングルトンインスタンスへの参照
     */
	static T* Instance() {
		return &instance;
	}
private:
	//! 管理するシングルトンインスタンスを指します。
	static T instance;
protected:
    /**
     * @brief コンストラクタ
     *
     * シングルトンインスタンスの生成を防ぐためにprotectedにしています。
     */
    Singleton() = default;

    /**
     * @brief デストラクタ
     *
     * シングルトンインスタンスの破棄を防ぐためにprotectedにしています。
     */
    ~Singleton() = default;

    /**
     * @brief コピーコンストラクタ（削除）
     *
     * シングルトンパターンを維持するために削除しています。
     */
    Singleton(const Singleton&) = delete;

    /**
     * @brief 代入演算子（削除）
     *
     * シングルトンパターンを維持するために削除しています。
     *
     * @return Singleton& 自身への参照
     */
    Singleton& operator=(const Singleton&) = delete;
};

template <typename T>
T Singleton<T>::instance;

#endif // !_SINGLETON_H_



