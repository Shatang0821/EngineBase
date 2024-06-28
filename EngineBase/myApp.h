/**
 * @file MyApp.h
 * @brief �Q�[���A�v���P�[�V�����̊�ՂƂȂ�N���X
 *
 * ���̃t�@�C���ɂ́A�Q�[���S�̂̊Ǘ����s��MyApp�N���X����`����Ă��܂��B
 * MyApp�N���X�̓V���O���g���p�^�[�����g�p���Ď�������Ă���A
 * �Q�[���̏������A���C�����[�v�A���\�[�X�̉���Ȃǂ̊�{�I�ȋ@�\��񋟂��܂��B
 *
 * @date 2024/06/28
 * @author �T�g�E
 */

#ifndef _MYAPP_H_
#define _MYAPP_H_

#include "Singleton.h"
#include "Timer.h"
#include "World.h"

 /**
  * @enum GameState
  * @brief �Q�[���S�̂̏�ԑJ�ڂ�\���񋓌^
  *
  * �Q�[���̊e�t�F�[�Y�i�J�n�҂��A�i�s���A�N���A�j���`���܂��B
  */
enum GameState
{
	GAME_STATE_READY,    ///< �Q�[���J�n�҂�
	GAME_STATE_PLAYING,  ///< �Q�[���i�s��
	GAME_STATE_CLEAR,    ///< �X�e�[�W�N���A

	GAME_STATE_COUNT,    ///< ��Ԃ̐���\��
	GAME_STATE_INVALID = -1, ///< �����ȏ��
};

/**
 * @class MyApp
 * @brief �Q�[���A�v���P�[�V�����̊�ՃN���X
 *
 * MyApp�N���X�́A�V���O���g���p�^�[�����g�p���āA
 * �Q�[���A�v���P�[�V�����̏������A���C�����[�v�A���\�[�X�̉���Ȃǂ��Ǘ����܂��B
 */
class MyApp : public Singleton<MyApp>
{
	// Singleton�N���X��MyApp�̃v���C�x�[�g�R���X�g���N�^�ɃA�N�Z�X�ł���悤�ɂ���
	friend class Singleton<MyApp>;
protected:
	/**
	 * @brief �R���X�g���N�^
	 *
	 * �V���O���g���p�^�[�����ێ����邽�߂�protected�ɂ��Ă��܂��B
	 */
	MyApp() {
	};
	/**
	 * @brief �f�X�g���N�^
	 *
	 * �V���O���g���p�^�[�����ێ����邽�߂�protected�ɂ��Ă��܂��B
	 */
	~MyApp() {};

public:
	/**
	 * @brief �A�v���P�[�V����������������
	 *
	 * �Q�[���̏������������s���܂��B
	 *
	 * @return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
	 */
	bool	InitApp();
	/**
	 * @brief ���C�����[�v�����s����
	 *
	 * �Q�[���̃��C�����[�v�����s���܂��B�ʏ�A���̊֐��̓Q�[���̃��C�����[�v���I������܂ŌĂяo����܂��B
	 */
	void	MainLoop();
	/**
	 * @brief ���\�[�X���������
	 *
	 * �Q�[���Ŏg�p�������\�[�X�̉���������s���܂��B
	 */
	void	ReleaseData();
};

#endif // !_MYAPP_H_



