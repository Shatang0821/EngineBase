/**
 * @file SpriteRenderer.h
 * @brief �X�v���C�g�����_���[�N���X�̒�`
 *
 * ���̃t�@�C���ɂ́A�X�v���C�g��`�悷�邽�߂�SpriteRenderer�N���X����`����Ă��܂��B
 * SpriteRenderer�N���X�́A�V�[���R���|�[�l���g�A���C���[�C���^�[�t�F�[�X�A�摜�C���^�[�t�F�[�X��
 * �p�����Ă���A�����̋@�\�𓝍����ăX�v���C�g�̕`����s���܂��B
 *
 * @date 2024/06/29
 * @autor �T�g�E
 */
#ifndef _SPRITERENDERER_H_
#define _SPRITERENDERER_H_

#include "SceneComponent.h"
#include "VisualInterface.h"

 /**
  * @class SpriteRenderer
  * @brief �X�v���C�g��`�悷�邽�߂̃N���X
  *
  * ���̃N���X�́A�V�[���R���|�[�l���g�A���C���[�C���^�[�t�F�[�X�A�摜�C���^�[�t�F�[�X��
  * �p�����A�X�v���C�g�̕`��@�\��񋟂��܂��B�ŏI�N���X�ifinal�j�Ƃ��Đ錾����Ă���A
  * �h���N���X���쐬���邱�Ƃ͂ł��܂���B
  */
class SpriteRenderer final: public SceneComponent,public LayerInterface,public ImageInterface
{
public:
    /**
     * @brief �X�v���C�g��`�悷��
     *
     * ���̃��\�b�h�́ALayerInterface����p�����ꂽRender���\�b�h���I�[�o�[���C�h���A
     * �X�v���C�g�̕`�揈�����������܂��B
     */
	virtual void Render() override;
};

#endif // !_SPRITERENDERER_H_



