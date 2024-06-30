#pragma once
#include <cmath>
#include <random>

/**
 * @class Math
 * @brief 数学的な関数を提供するユーティリティクラス
 *
 * このクラスは、数学的な操作やランダムな数値の生成など、汎用的な
 * 数学関数を提供します。
 */
class Math
{
	
public:
	/**
	 * @brief 指定された範囲内のランダムな整数を生成します
	 *
	 * この関数は、指定された範囲 [lower, upper] 内のランダムな整数を生成します。
	 * lower が upper より大きい場合は、値を入れ替えます。
	 *
	 * @param lower 範囲の下限
	 * @param upper 範囲の上限
	 * @return int 範囲内のランダムな整数
	 */
	static int RandInt(int lower, int upper) {
		// lower と upper の値が逆の場合、入れ替える
		if (lower > upper) {
			int temp = lower;
			lower = upper;
			upper = temp;
		}

		// ランダムデバイスと生成器、および分布を設定
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(lower, upper);

		// ランダムな整数を生成して返す
		return dis(gen);
	}

	/**
	 * @brief 指定された範囲内のランダムな実数を生成します
	 *
	 * この関数は、指定された範囲 [lower, upper] 内のランダムな実数を生成します。
	 * lower が upper より大きい場合は、値を入れ替えます。
	 *
	 * @param lower 範囲の下限
	 * @param upper 範囲の上限
	 * @return double 範囲内のランダムな実数
	 */
	static double RandReal(double lower, double upper) {
		// lower と upper の値が逆の場合、入れ替える
		if (lower > upper) {
			double temp = lower;
			lower = upper;
			upper = temp;
		}

		// ランダムデバイスと生成器、および分布を設定
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(lower, upper);

		// ランダムな実数を生成して返す
		return dis(gen);
	}

	/**
	* @brief 0.0から1.0の範囲内のランダムな実数を生成します
	*
	* この関数は、0.0から1.0の範囲内でランダムな実数を生成します。
	*
	* @return double 0.0から1.0の範囲内のランダムな実数
	*/
	static double RandPerc() {
		// ランダムデバイスと生成器、および分布を設定
		std::random_device rd;
		std::mt19937 gen(rd());

		// 0.0から1.0の範囲内でランダムな実数を生成して返す
		return std::generate_canonical<double, 10>(gen);
	}

	/**
 * @brief 値を指定された範囲内にクランプするテンプレート関数
 *
 * この関数は、指定された値を最小値と最大値の範囲内にクランプします。
 * 値が最小値より小さい場合は最小値を、最大値より大きい場合は最大値を返します。
 *
 * @tparam T 値の型
 * @param value クランプする値
 * @param min 最小値
 * @param max 最大値
 * @return T クランプされた値
 */
	template<typename T>
	static T clamp(T value, T min, T max) {
		if (value < min) {
			return min;
		}
		else if (value > max) {
			return max;
		}
		else {
			return value;
		}
	}
};