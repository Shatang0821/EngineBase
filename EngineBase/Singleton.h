/**
 * @file Singleton.h
 * @brief �V���O���g���̃e���v���[�g�ƂȂ�
 *
 * ���̃t�@�C���ɂ́A�V���O���g���p�^�[�����������邽�߂̊��e���v���[�g�N���X����`����Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

 /**
  * @class Singleton
  * @brief �V���O���g���N���X�̊��e���v���[�g
  *
  * ���̃N���X�́A�V���O���g���p�^�[�����������邽�߂̊��e���v���[�g�N���X�ł��B
  *
  * @tparam T �Ǘ�����N���X�̌^
  */
template <typename T>
class Singleton
{
public:
    /**
     * @brief �C���X�^���X���擾����
     *
     * ���̊֐��́A�V���O���g���C���X�^���X���擾���܂��B
     *
     * @return T& �V���O���g���C���X�^���X�ւ̎Q��
     */
	static T* Instance() {
		return &instance;
	}
private:
	//! �Ǘ�����V���O���g���C���X�^���X���w���܂��B
	static T instance;
protected:
    /**
     * @brief �R���X�g���N�^
     *
     * �V���O���g���C���X�^���X�̐�����h�����߂�protected�ɂ��Ă��܂��B
     */
    Singleton() = default;

    /**
     * @brief �f�X�g���N�^
     *
     * �V���O���g���C���X�^���X�̔j����h�����߂�protected�ɂ��Ă��܂��B
     */
    ~Singleton() = default;

    /**
     * @brief �R�s�[�R���X�g���N�^�i�폜�j
     *
     * �V���O���g���p�^�[�����ێ����邽�߂ɍ폜���Ă��܂��B
     */
    Singleton(const Singleton&) = delete;

    /**
     * @brief ������Z�q�i�폜�j
     *
     * �V���O���g���p�^�[�����ێ����邽�߂ɍ폜���Ă��܂��B
     *
     * @return Singleton& ���g�ւ̎Q��
     */
    Singleton& operator=(const Singleton&) = delete;
};

template <typename T>
T Singleton<T>::instance;

#endif // !_SINGLETON_H_



