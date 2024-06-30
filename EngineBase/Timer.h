/**
 * @file Timer.h
 * @brief 時間と関係するクラス
 *

 * @author サトウ
 * @date 2024/06/25
 */
#ifndef _TIMER_H_
#define _TIMER_H_



#include "World.h"

 /**
   * @class Timer
   * @brief 時間と関係するクラス
   */
class Timer final
{
public:
	Timer() { lastTime = std::chrono::steady_clock::now(); }
	~Timer() { mainWorld.GameTimers.erase(this); }
	/**
	 * @brief 処理のバインド
	 *
	 * 指定された型の関数をコールバックにバインド
	 *
	 * @tparam T 関数が属するオブジェクトの型
	 * @param duration 呼び出し間隔（秒単位）
	 * @param obj 関数を持つオブジェクトのポインタ
	 * @param func 呼び出すメンバ関数のポインタ
	 * @param repeat 呼び出しを繰り返すかどうか（デフォルトはfalse）
	 */
	template<typename T>
	void Bind(double duration, T* obj,void(T::*func)(),bool repeat = false) {
		callback = std::bind(func, obj);
		 
		delay = std::chrono::duration<double>(duration);
		lastTime = std::chrono::steady_clock::now();
		bPersistent = repeat;
		mainWorld.GameTimers.insert(this);
	}

	/**
	 * @brief 設定された遅延時間が経過した場合にコールバック関数を実行します。
	 *
	 * この関数は、設定された遅延時間が経過したかどうかを確認し、経過している場合は
	 * コールバック関数を実行します。その後、現在の時間を最後に記録された時間として更新します。
	 * `bPersistent` が false の場合、遅延時間をリセットします。
	 *
	 * @details
	 * - `delay` が正の値を持つことを確認します。
	 * - 現在の経過時間が設定された `delay` を超える場合に `callback` を実行します。
	 * - `callback` 実行後に `lastTime` を現在の時間に更新します。
	 * - `bPersistent` が false の場合、`delay` を 0 にリセットします。callBack一回だけ実行する
	 */
	void Execute();
	/**
	 * @brief 最後に記録された時間からの経過時間を取得します。
	 *
	 * この関数は、最後に記録された時間からの経過時間を秒単位で返します。
	 *
	 * @return double 最後に記録された時間からの経過時間（秒）。
	 */
	double GetDelay();
	/**
	 * @brief 遅延時間を設定します。
	 *
	 * この関数は、遅延時間を秒単位で設定します。
	 *
	 * @param time 設定する遅延時間（秒）。
	 */
	void SetDelay(double time);
	/**
	 * @brief 最後の時間記録を現在の時間にリセットします。
	 *
	 * この関数は、`lastTime` を現在の時間にリセットします。
	 */
	void Reset();
	/**
	 * @brief 遅延を停止します。
	 *
	 * この関数は、遅延時間を 0 にリセットし、遅延を停止します。
	 */
	void Stop();
private:
	//! バインドする関数ポインタ
	std::function<void()> callback;
	//! 重複トリガー
	bool bPersistent = false;
	//! 間隔
	std::chrono::duration<double>delay = std::chrono::duration<double>(0);
	//! 最後に記録した時間ポイント
	std::chrono::time_point<std::chrono::steady_clock>lastTime;

	/**
	 * @brief 最後に記録された時間からの経過時間を返します。
	 *
	 * この関数は、現在の時間と最後に記録された時間との差を
	 * std::chrono::steady_clock を使用して計算します。返される時間は、秒単位の
	 * double 精度の duration で表されます。
	 *
	 * @return std::chrono::duration<double> 最後に記録された時間からの経過時間。
	 */
	std::chrono::duration<double> getDelay() {
		return std::chrono::steady_clock::now() - lastTime;
	}

};
#endif // !_TIMER_H_




