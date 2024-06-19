/**
 * @file Transform.h
 * @brief �ʒu�A��]�A�X�P�[����\���\���̂ƂȂ�
 *
 * ���̃t�@�C���ɂ́A�ϊ���񂪒�`����Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Vector2.h"

/**
 * @struct Transform
 * @brief �ʒu�A��]�A�X�P�[����\���\����
 *
 * ���̍\���̂́A�I�u�W�F�N�g�̈ʒu�A��]�A�X�P�[�����Ǘ����܂��B
 */
struct Transform
{
    Vector2 position;    /**< �ʒu */
    float rotation;      /**< ��](�x���@) */
    Vector2 scale;       /**< �X�P�[�� */

    /**
     * @brief �f�t�H���g�R���X�g���N�^
     *
     * �ʒu��(0, 0)�A��]��0�A�X�P�[����(1, 1)�ɏ��������܂��B
     */
    Transform() :position(0, 0), rotation(0), scale(1, 1) {}

    /**
    * @brief �p�����[�^�t���R���X�g���N�^
    *
    * �w�肳�ꂽ�ʒu�A��]�A�X�P�[���ŏ��������܂��B
    *
    * @param pos ����������ʒu
    * @param rot �����������]
    * @param scale ����������X�P�[��
    */
    Transform(const Vector2& pos, float rot, const Vector2& scale)
        :position(pos), rotation(rot), scale(scale) {}

    /**
     * @brief �P�ʕϊ���Ԃ��֐�
     *
     * �ʒu��(0, 0)�A��]��0�A�X�P�[����(1, 1)�ɐݒ肵��Transform�I�u�W�F�N�g��Ԃ��܂��B
     *
     * @return Transform �P�ʕϊ���\��Transform�I�u�W�F�N�g
     */
    Transform Identity() const {
        return Transform(Vector2::Zero(), 0, Vector2::One());
    }
};

#endif // !_TRANSFORM_H_

