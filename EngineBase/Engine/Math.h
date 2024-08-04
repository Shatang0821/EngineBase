#pragma once
#include <cmath>
#include <random>

/**
 * @class Math
 * @brief ���w�I�Ȋ֐���񋟂��郆�[�e�B���e�B�N���X
 *
 * ���̃N���X�́A���w�I�ȑ���⃉���_���Ȑ��l�̐����ȂǁA�ėp�I��
 * ���w�֐���񋟂��܂��B
 */
class Math
{
	
public:
	/**
	 * @brief �w�肳�ꂽ�͈͓��̃����_���Ȑ����𐶐����܂�
	 *
	 * ���̊֐��́A�w�肳�ꂽ�͈� [lower, upper] ���̃����_���Ȑ����𐶐����܂��B
	 * lower �� upper ���傫���ꍇ�́A�l�����ւ��܂��B
	 *
	 * @param lower �͈͂̉���
	 * @param upper �͈͂̏��
	 * @return int �͈͓��̃����_���Ȑ���
	 */
	static int RandInt(int lower, int upper) {
		// lower �� upper �̒l���t�̏ꍇ�A����ւ���
		if (lower > upper) {
			int temp = lower;
			lower = upper;
			upper = temp;
		}

		// �����_���f�o�C�X�Ɛ�����A����ѕ��z��ݒ�
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(lower, upper);

		// �����_���Ȑ����𐶐����ĕԂ�
		return dis(gen);
	}

	/**
	 * @brief �w�肳�ꂽ�͈͓��̃����_���Ȏ����𐶐����܂�
	 *
	 * ���̊֐��́A�w�肳�ꂽ�͈� [lower, upper] ���̃����_���Ȏ����𐶐����܂��B
	 * lower �� upper ���傫���ꍇ�́A�l�����ւ��܂��B
	 *
	 * @param lower �͈͂̉���
	 * @param upper �͈͂̏��
	 * @return double �͈͓��̃����_���Ȏ���
	 */
	static double RandReal(double lower, double upper) {
		// lower �� upper �̒l���t�̏ꍇ�A����ւ���
		if (lower > upper) {
			double temp = lower;
			lower = upper;
			upper = temp;
		}

		// �����_���f�o�C�X�Ɛ�����A����ѕ��z��ݒ�
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(lower, upper);

		// �����_���Ȏ����𐶐����ĕԂ�
		return dis(gen);
	}

	/**
	* @brief 0.0����1.0�͈͓̔��̃����_���Ȏ����𐶐����܂�
	*
	* ���̊֐��́A0.0����1.0�͈͓̔��Ń����_���Ȏ����𐶐����܂��B
	*
	* @return double 0.0����1.0�͈͓̔��̃����_���Ȏ���
	*/
	static double RandPerc() {
		// �����_���f�o�C�X�Ɛ�����A����ѕ��z��ݒ�
		std::random_device rd;
		std::mt19937 gen(rd());

		// 0.0����1.0�͈͓̔��Ń����_���Ȏ����𐶐����ĕԂ�
		return std::generate_canonical<double, 10>(gen);
	}

	
	static float Lerp(float a, float b, float t) {
		t = clamp(t, 0.001f, 0.1f);
		return a + (b - a) * t;
	}

	/**
	 * @brief �w�肳�ꂽ�l���w�肳�ꂽ�͈͓��ɃN�����v���܂�
	 *
	 * ���̊֐��́A�w�肳�ꂽ�l value ��͈� [min, max] ���ɃN�����v���܂��B
	 * value �� min ��菬�����ꍇ�� min �ɁAmax ���傫���ꍇ�� max �ɐݒ肳��܂��B
	 *
	 * @param value �N�����v����l
	 * @param min �͈͂̉���
	 * @param max �͈͂̏��
	 * @return T �N�����v���ꂽ�l
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