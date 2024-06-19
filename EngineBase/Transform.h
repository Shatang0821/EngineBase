#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Vector2.h"
//トランスフォーマー
struct Transform
{
    Vector2 position;   //位置
    float rotation;     //回転
    Vector2 scale;      //スケール

    Transform() :position(0, 0), rotation(0), scale(1, 1) {}
    Transform(const Vector2& pos, float rot, const Vector2& scale)
        :position(pos), rotation(rot), scale(scale) {}

    Transform Identity() const {
        return Transform(Vector2::Zero(), 0, Vector2::One());
    }
};

#endif // !_TRANSFORM_H_

