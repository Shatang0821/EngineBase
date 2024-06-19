#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Vector2.h"
//�g�����X�t�H�[�}�[
struct Transform
{
    Vector2 position;   //�ʒu
    float rotation;     //��]
    Vector2 scale;      //�X�P�[��

    Transform() :position(0, 0), rotation(0), scale(1, 1) {}
    Transform(const Vector2& pos, float rot, const Vector2& scale)
        :position(pos), rotation(rot), scale(scale) {}

    Transform Identity() const {
        return Transform(Vector2::Zero(), 0, Vector2::One());
    }
};

#endif // !_TRANSFORM_H_

