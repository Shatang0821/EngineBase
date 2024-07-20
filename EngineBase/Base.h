/**
 * @file Base.h
 * @brief 基底クラスとなる
 *
 * このファイルには、ゲーム内すべての基底クラスであるBaseクラスが定義されています。
 * 
 * @author サトウ
 * @date 2024/06/19
 */
#ifndef _BASE_H_
#define _BASE_H_

 /**
  * @class Base
  * @brief 基底クラス
  *
  * すべての基底クラスとなる抽象クラスです。
  */
class Base
{
public:
    /**
     * @brief 更新処理の純粋仮想関数
     *
     * すべての派生クラスで実装する必要がある更新処理です。
     *
     * @param DeltaTime 前フレームからの経過時間
     */
    virtual void Update(float DeltaTime) = 0;

    /**
	 * @brief 固定更新処理の純粋仮想関数
	 *
	 * すべての派生クラスで実装する必要がある固定更新処理です。
	 *
	 * @param fixedDeltaTime 固定経過時間
	 */
    virtual void FixedUpdate(float fixedDeltaTime) = 0;
};

#endif // !_BASE_H_

