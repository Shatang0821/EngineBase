/**
 * @file StaticMesh.h
 * @brief �ÓI���b�V���N���X�̒�`
 *
 * ���̃t�@�C���ɂ́AStaticMesh�N���X����`����Ă��܂��B
 * StaticMesh�N���X�́A�ÓI�ȃ��b�V���I�u�W�F�N�g��\���A
 * �X�v���C�g�����_���[���g�p���ĕ`����s���܂��B
 *
 * @date 2024/06/29
 * @author �T�g�E
 */
#ifndef _STATICMESH_H_
#define _STATICMESH_H_

#include "Object.h"
#include "SpriteRenderer.h"

 /**
  * @class StaticMesh
  * @brief �ÓI���b�V���I�u�W�F�N�g��\���N���X
  *
  * ���̃N���X�́A�ÓI�ȃ��b�V���I�u�W�F�N�g��\���A
  * �X�v���C�g�����_���[���g�p���ĕ`����s���܂��B
  * Object�N���X�����N���X�Ƃ��A���b�V���̕`���SpriteRenderer���g�p���܂��B
  */
class StaticMesh : public Object
{
private:
    //! �X�v���C�g��`�悷�邽�߂̃����_���[
	SpriteRenderer* renderer;
public:
    /**
     * @brief �R���X�g���N�^
     *
     * StaticMesh�N���X�̃C���X�^���X�����������܂��B
     * �X�v���C�g�����_���[�̃C���X�^���X���쐬���A���������܂��B
     */
	StaticMesh();
};

#endif // !_STATICMESH_H_


