/**
 * @file Vector2.h
 * @brief 2D�x�N�g����\���\���̂ƂȂ�
 *
 * ���̃t�@�C���ɂ́A2D�x�N�g������`����Ă��܂��B
 *
 * @author �T�g�E
 * @date 2024/06/19
 */
#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <iostream>

/**
 * @struct Vector2
 * @brief 2D�x�N�g����\���\����
 *
 * ���̍\���̂́A2D�x�N�g���̊�{�I�ȑ����񋟂��܂��B
 */
struct Vector2
{

    //! X���W
    float x;
    //! Y���W
    float y;

    /**
      * @brief �f�t�H���g�R���X�g���N�^
      *
      * X���W��Y���W���w�肳�ꂽ�l�ŏ��������܂��B
      *
      * @param x X���W
      * @param y Y���W
      */
    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    /**
     * @brief �x�N�g���̉��Z
     *
     * 2�̃x�N�g�������Z���܂��B
     *
     * @param v ���Z����x�N�g��
     * @return Vector2 ���Z����
     */
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    /**
     * @brief �x�N�g���̉��Z�Ƒ��
     *
     * �x�N�g�������Z���A���̌��ʂ������܂��B
     *
     * @param v ���Z����x�N�g��
     * @return Vector2& ���Z����
     */
    Vector2& operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    /**
     * @brief �x�N�g���̌��Z
     *
     * 2�̃x�N�g�������Z���܂��B
     *
     * @param v ���Z����x�N�g��
     * @return Vector2 ���Z����
     */
    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    /**
     * @brief �x�N�g���̌��Z�Ƒ��
     *
     * �x�N�g�������Z���A���̌��ʂ������܂��B
     *
     * @param v ���Z����x�N�g��
     * @return Vector2& ���Z����
     */
    Vector2& operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    /**
     * @brief �x�N�g���̏�Z
     *
     * 2�̃x�N�g������Z���܂��B
     *
     * @param v ��Z����x�N�g��
     * @return Vector2 ��Z����
     */
    Vector2 operator*(const Vector2& v) const {
        return Vector2(x * v.x, y * v.y);
    }

    /**
     * @brief �x�N�g���̏�Z�Ƒ��
     *
     * �x�N�g������Z���A���̌��ʂ������܂��B
     *
     * @param v ��Z����x�N�g��
     * @return Vector2& ��Z����
     */
    Vector2& operator*=(const Vector2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    /**
     * @brief �X�J���[��Z
     *
     * �x�N�g���ɃX�J���[����Z���܂��B
     *
     * @param scalar ��Z����X�J���[�l
     * @return Vector2 ��Z����
     */
    Vector2 operator*(const float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    /**
     * @brief �X�J���[��Z�Ƒ��
     *
     * �x�N�g���ɃX�J���[����Z���A���̌��ʂ������܂��B
     *
     * @param scalar ��Z����X�J���[�l
     * @return Vector2& ��Z����
     */
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    /**
     * @brief �x�N�g���̑傫���i�����j���v�Z���܂��B
     *
     * @return float �x�N�g���̑傫��
     */
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    /**
     * @brief �x�N�g���𐳋K�����܂�
     *
     * @return Vector2 ���K�����ꂽ�x�N�g��
     */
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag == 0) return Vector2(0, 0);
        return Vector2(x / mag, y / mag);
    }

    /**
     * @brief �x�N�g���̓��ς��v�Z���܂�
     *
     * @param v ���ς��v�Z����x�N�g��
     * @return float ����
     */
    float dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    /**
     * @brief 2�̃x�N�g���Ԃ̋������v�Z���܂�
     *
     * @param v �������v�Z����x�N�g��
     * @return float ����
     */
    float distance(const Vector2& v) const {
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }

    /**
     * @brief 2�̃x�N�g���̊Ԃ̊p�x���v�Z���܂�
     *
     * @param v �p�x���v�Z����x�N�g��
     * @return float ���W�A���P�ʂ̊p�x
     */
    float angleBetween(const Vector2& v) const {
        float dotProd = dot(v);
        float magProd = magnitude() * v.magnitude();
        return std::acos(dotProd / magProd); // ���W�A���P�ʂ̊p�x
    }

    /**
     * @brief �x�N�g���̐��^��Ԃ��v�Z���܂�
     *
     * @param v ��Ԃ���x�N�g��
     * @param t ��ԌW���i0����1�͈̔́j
     * @return Vector2 ���^��Ԃ��ꂽ�x�N�g��
     */
    Vector2 lerp(const Vector2& v, float t) const {
        return *this + (v - *this) * t;
    }

    /**
     * @brief �[���x�N�g����Ԃ��ÓI���\�b�h
     *
     * @return Vector2 (0.0f, 0.0f) �̃x�N�g��
     */
    static Vector2 Zero() {
        return Vector2(0.0f, 0.0f);
    }

    /**
     * @brief �P�ʃx�N�g����Ԃ��ÓI���\�b�h
     *
     * @return Vector2 (1.0f, 1.0f) �̃x�N�g��
     */
    static Vector2 One() {
        return Vector2(1.0f, 1.0f);
    }
};

/**
 * @brief �x�N�g����W���o�͂���I�[�o�[���[�h���Z�q
 *
 * @param out �o�̓X�g���[��
 * @param vec �o�͂���x�N�g��
 * @return std::ostream& �o�̓X�g���[��
 */
static std::ostream& operator<<(std::ostream& out, const Vector2& vec)
{
    std::cout << "(" << vec.x << "," << vec.y << ")";
    return out;
}
#endif // !_VECTOR2_H_




