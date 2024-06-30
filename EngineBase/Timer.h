/**
 * @file Timer.h
 * @brief ���ԂƊ֌W����N���X
 *

 * @author �T�g�E
 * @date 2024/06/25
 */
#ifndef _TIMER_H_
#define _TIMER_H_



#include "World.h"

 /**
   * @class Timer
   * @brief ���ԂƊ֌W����N���X
   */
class Timer final
{
public:
	Timer() { lastTime = std::chrono::steady_clock::now(); }
	~Timer() { mainWorld.GameTimers.erase(this); }
	/**
	 * @brief �����̃o�C���h
	 *
	 * �w�肳�ꂽ�^�̊֐����R�[���o�b�N�Ƀo�C���h
	 *
	 * @tparam T �֐���������I�u�W�F�N�g�̌^
	 * @param duration �Ăяo���Ԋu�i�b�P�ʁj
	 * @param obj �֐������I�u�W�F�N�g�̃|�C���^
	 * @param func �Ăяo�������o�֐��̃|�C���^
	 * @param repeat �Ăяo�����J��Ԃ����ǂ����i�f�t�H���g��false�j
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
	 * @brief �ݒ肳�ꂽ�x�����Ԃ��o�߂����ꍇ�ɃR�[���o�b�N�֐������s���܂��B
	 *
	 * ���̊֐��́A�ݒ肳�ꂽ�x�����Ԃ��o�߂������ǂ������m�F���A�o�߂��Ă���ꍇ��
	 * �R�[���o�b�N�֐������s���܂��B���̌�A���݂̎��Ԃ��Ō�ɋL�^���ꂽ���ԂƂ��čX�V���܂��B
	 * `bPersistent` �� false �̏ꍇ�A�x�����Ԃ����Z�b�g���܂��B
	 *
	 * @details
	 * - `delay` �����̒l�������Ƃ��m�F���܂��B
	 * - ���݂̌o�ߎ��Ԃ��ݒ肳�ꂽ `delay` �𒴂���ꍇ�� `callback` �����s���܂��B
	 * - `callback` ���s��� `lastTime` �����݂̎��ԂɍX�V���܂��B
	 * - `bPersistent` �� false �̏ꍇ�A`delay` �� 0 �Ƀ��Z�b�g���܂��BcallBack��񂾂����s����
	 */
	void Execute();
	/**
	 * @brief �Ō�ɋL�^���ꂽ���Ԃ���̌o�ߎ��Ԃ��擾���܂��B
	 *
	 * ���̊֐��́A�Ō�ɋL�^���ꂽ���Ԃ���̌o�ߎ��Ԃ�b�P�ʂŕԂ��܂��B
	 *
	 * @return double �Ō�ɋL�^���ꂽ���Ԃ���̌o�ߎ��ԁi�b�j�B
	 */
	double GetDelay();
	/**
	 * @brief �x�����Ԃ�ݒ肵�܂��B
	 *
	 * ���̊֐��́A�x�����Ԃ�b�P�ʂŐݒ肵�܂��B
	 *
	 * @param time �ݒ肷��x�����ԁi�b�j�B
	 */
	void SetDelay(double time);
	/**
	 * @brief �Ō�̎��ԋL�^�����݂̎��ԂɃ��Z�b�g���܂��B
	 *
	 * ���̊֐��́A`lastTime` �����݂̎��ԂɃ��Z�b�g���܂��B
	 */
	void Reset();
	/**
	 * @brief �x�����~���܂��B
	 *
	 * ���̊֐��́A�x�����Ԃ� 0 �Ƀ��Z�b�g���A�x�����~���܂��B
	 */
	void Stop();
private:
	//! �o�C���h����֐��|�C���^
	std::function<void()> callback;
	//! �d���g���K�[
	bool bPersistent = false;
	//! �Ԋu
	std::chrono::duration<double>delay = std::chrono::duration<double>(0);
	//! �Ō�ɋL�^�������ԃ|�C���g
	std::chrono::time_point<std::chrono::steady_clock>lastTime;

	/**
	 * @brief �Ō�ɋL�^���ꂽ���Ԃ���̌o�ߎ��Ԃ�Ԃ��܂��B
	 *
	 * ���̊֐��́A���݂̎��ԂƍŌ�ɋL�^���ꂽ���ԂƂ̍���
	 * std::chrono::steady_clock ���g�p���Čv�Z���܂��B�Ԃ���鎞�Ԃ́A�b�P�ʂ�
	 * double ���x�� duration �ŕ\����܂��B
	 *
	 * @return std::chrono::duration<double> �Ō�ɋL�^���ꂽ���Ԃ���̌o�ߎ��ԁB
	 */
	std::chrono::duration<double> getDelay() {
		return std::chrono::steady_clock::now() - lastTime;
	}

};
#endif // !_TIMER_H_




