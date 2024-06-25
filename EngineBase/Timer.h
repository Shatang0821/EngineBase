/**
 * @file Timer.h
 * @brief 時間と関係するクラス
 *

 * @author サトウ
 * @date 2024/06/25
 */
#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
 /**
   * @class Timer
   * @brief 時間と関係するクラス
   */
class Timer final
{
public:

	/**
	 * @brief 処理のバインド
	 *
	 * 指定された型の関数をコールバックにバインド
	 *
	 * @tparam T 関数が属するオブジェクトの型
	 * @param delay 呼び出し間隔（秒単位）
	 * @param obj 関数を持つオブジェクトのポインタ
	 * @param func 呼び出すメンバ関数のポインタ
	 * @param repeat 呼び出しを繰り返すかどうか（デフォルトはfalse）
	 */
	template<typename T>
	void Bind(double delay, T* obj,void(T::*func)(),bool repeat = false) {
		callback = std::bind(func, obj);

		bPersistent = repeat;
	}
private:
	//! バインドする関数ポインタ
	std::function<void()> callback;
	//! 重複トリガー
	bool bPersistent = false;
	//! 間隔
	std::chrono::duration<double>delay = std::chrono::duration<double>(0);
};
#endif // !_TIMER_H_




