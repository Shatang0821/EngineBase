/**
 * @file Timer.h
 * @brief ���ԂƊ֌W����N���X
 *

 * @author �T�g�E
 * @date 2024/06/25
 */
#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
 /**
   * @class Timer
   * @brief ���ԂƊ֌W����N���X
   */
class Timer final
{
public:

	/**
	 * @brief �����̃o�C���h
	 *
	 * �w�肳�ꂽ�^�̊֐����R�[���o�b�N�Ƀo�C���h
	 *
	 * @tparam T �֐���������I�u�W�F�N�g�̌^
	 * @param delay �Ăяo���Ԋu�i�b�P�ʁj
	 * @param obj �֐������I�u�W�F�N�g�̃|�C���^
	 * @param func �Ăяo�������o�֐��̃|�C���^
	 * @param repeat �Ăяo�����J��Ԃ����ǂ����i�f�t�H���g��false�j
	 */
	template<typename T>
	void Bind(double delay, T* obj,void(T::*func)(),bool repeat = false) {
		callback = std::bind(func, obj);

		bPersistent = repeat;
	}
private:
	//! �o�C���h����֐��|�C���^
	std::function<void()> callback;
	//! �d���g���K�[
	bool bPersistent = false;
	//! �Ԋu
	std::chrono::duration<double>delay = std::chrono::duration<double>(0);
};
#endif // !_TIMER_H_




