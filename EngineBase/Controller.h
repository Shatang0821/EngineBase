#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"

class Controller :public Object
{
protected:
	class Camera* camera;
public:
	Controller();

	/**
	 * @brief �Q�[���v���C�̊J�n���ɌĂяo����郁�\�b�h
	 *
	 * ���̊֐��́A�Q�[���v���C���J�n�����Ƃ��ɏ������������s�����߂ɌĂяo����܂��B
	 * �e�N���X�� `BeginPlay` ���\�b�h���I�[�o�[���C�h���āA�J�����̏������������������܂��B
	 */
	virtual void BeginPlay() override;

	//���͏���
	void PickInfo(){}
};

#endif // !_CONTROLLER_H_

