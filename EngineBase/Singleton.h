/**
 * @file Singleton.h
 * @brief �V���O���g���̃e���v���[�g�ƂȂ�
 *
 * ���̃t�@�C���ɂ́A�V���O���g���p�^�[�����������邽�߂̊��e���v���[�g�N���X����`����Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */

#ifndef _MANAGER_H_
#define _MANAGER_H_

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
	 * �C���X�^���X�����݂��Ȃ��ꍇ�́A�V�����쐬����܂��B
	 *
	 * @return T* �V���O���g���C���X�^���X�ւ̃|�C���^
	 */
	static T* instance() {
		if (!manager)
			manager = new T();
		return manager;
	}
private:
	//! �Ǘ�����V���O���g���C���X�^���X���w���܂��B
	static T* manager;
protected:
    /**
     * @brief �R���X�g���N�^
     *
     * �V���O���g���C���X�^���X�̐�����h�����߂�protected�ɂ��Ă��܂��B
     */
    Manager() = default;

    /**
     * @brief �f�X�g���N�^
     *
     * �V���O���g���C���X�^���X�̔j����h�����߂�protected�ɂ��Ă��܂��B
     */
    ~Manager() = default;

    /**
     * @brief �R�s�[�R���X�g���N�^�i�폜�j
     *
     * �V���O���g���p�^�[�����ێ����邽�߂ɍ폜���Ă��܂��B
     */
    Manager(const Manager&) = delete;

    /**
     * @brief ������Z�q�i�폜�j
     *
     * �V���O���g���p�^�[�����ێ����邽�߂ɍ폜���Ă��܂��B
     *
     * @return Manager& ���g�ւ̎Q��
     */
    Manager& operator=(const Manager&) = delete;
};

template <typename T>
T* Singleton<T>::manager = nullptr;
#endif // !_MANAGER_H_



