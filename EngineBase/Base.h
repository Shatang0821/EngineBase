/**
 * @file Base.h
 * @brief ���N���X�ƂȂ�
 *
 * ���̃t�@�C���ɂ́A�Q�[�������ׂĂ̊��N���X�ł���Base�N���X����`����Ă��܂��B
 * 
 * @author �T�g�E
 * @date 2024/06/19
 */
#ifndef _BASE_H_
#define _BASE_H_

 /**
  * @class Base
  * @brief ���N���X
  *
  * ���ׂĂ̊��N���X�ƂȂ钊�ۃN���X�ł��B
  */
class Base
{
public:
    /**
     * @brief �X�V�����̏������z�֐�
     *
     * ���ׂĂ̔h���N���X�Ŏ�������K�v������X�V�����ł��B
     *
     * @param DeltaTime �O�t���[������̌o�ߎ���
     */
    virtual void Update(float DeltaTime) = 0;

    /**
	 * @brief �Œ�X�V�����̏������z�֐�
	 *
	 * ���ׂĂ̔h���N���X�Ŏ�������K�v������Œ�X�V�����ł��B
	 *
	 * @param fixedDeltaTime �Œ�o�ߎ���
	 */
    virtual void FixedUpdate(float fixedDeltaTime) = 0;
};

#endif // !_BASE_H_

