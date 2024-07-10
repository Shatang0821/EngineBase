/**
 * @file Controller.h
 * @brief �R���g���[���[���Ǘ�����N���X
 *
 * @author �T�g�E
 * @date 2024/06/30
 */
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"
#include "InputComponent.h"

 /**
  * @class Controller
  * @brief �Q�[���I�u�W�F�N�g�̃R���g���[���[�N���X
  *
  * ���̃N���X�́A�Q�[���I�u�W�F�N�g�̓��͏�����J����������Ǘ����܂��B
  * Object�N���X�����N���X�Ƃ��Čp�����Ă��܂��B
  */
class Controller :public Object
{
private:
	//! ���̓R���|�[�l���g
	InputComponent* inputComponent;
protected:
	//! �J�����I�u�W�F�N�g
	class Camera* camera;

	/**
	 * @brief ���̓R���|�[�l���g�̐ݒ���s���������z�֐�
	 *
	 * ���̊֐��́A�h���N���X�œ��̓R���|�[�l���g�̐ݒ���s�����߂Ɏ�������܂��B
	 */
	virtual void SetUpInputComponent(InputComponent* inputComponent) { ; }
public:
	/**
	 * @brief �R���X�g���N�^
	 *
	 * Controller�N���X�̃C���X�^���X�����������܂��B
	 */
	Controller();

	/**
	 * @brief �Q�[���v���C�̊J�n���ɌĂяo����郁�\�b�h
	 *
	 * ���̊֐��́A�Q�[���v���C���J�n�����Ƃ��ɏ������������s�����߂ɌĂяo����܂��B
	 * �e�N���X�� `BeginPlay` ���\�b�h���I�[�o�[���C�h���āA�J�����̏������������������܂��B
	 */
	virtual void BeginPlay() override;

	// ���͏���

};

#endif // !_CONTROLLER_H_

