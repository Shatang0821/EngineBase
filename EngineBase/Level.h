/**
 * @file Level.h
 * @brief �I�u�W�F�N�g��ێ�����N���X
 *
 * @author �T�g�E
 * @date 2024/06/21
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Base.h"

 /**
  * @class Level
  * @brief �V�[�����̃I�u�W�F�N�g���Ǘ�����N���X
  *
  * ���̃N���X�́A�V�[�����̃I�u�W�F�N�g���Ǘ�����
  */
class Level : public Base
{
public:
	virtual void Update(float DeltaTime) override;
};

#endif // !_LEVEL_H_



