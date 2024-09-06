/**
 * @file Animator.h
 * @brief �A�j���[�^�[�N���X�̒�`
 *
 * ���̃t�@�C���ɂ́AAnimator,Animation�N���X����`����Ă��܂��B
 * Animator�N���X�́A�A�j���[�V�����̍Đ���Ǘ����s���܂��B
 *
 * @date 2024/07/10
 * @autor �T�g�E
 */

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "myApp.h"
#include "Component.h"
#include "Timer.h"
#include "SpriteRenderer.h"
/**
 * @class Animation
 * @brief �A�j���[�V�����N���X
 *
 * ���̃N���X�́A�A�j���[�V�����̍Đ���Ǘ����s���܂��B
 * �A�j���[�V�����̃t���[�����[�g��C���f�b�N�X���Ǘ����A
 * �A�j���[�V�����̍Đ��𐧌䂵�܂��B
 */
class Animation 
{
	friend class Animator;
private:
	//! �A�j���[�V�����̃t���[�����[�g
	int num = 0;
	//! �A�j���[�V�����̃I�t�Z�b�g
	POINT offset = { 0,0 };
	//! �A�j���[�V�����̃C���f�b�N�X
	int index = 0;
	//! �A�j���[�V�����̔z��
	std::vector<MyTexture*> textures;
	//! ���v
	Timer clock;

public:
	Animation() {  }

	/**
	 * @brief �A�j���[�V�����̍X�V�ݒ�
	 * 
	 * @param loop ���[�v���邩�ǂ���
	 */
	void Bind(bool loop = true);

	void Load(ResID id, POINT delta = {0,0});

	/**
	 * @brief �A�j���[�V�����̍X�V�Ԋu��ݒ肵�܂�
	 */
	void SetInterVal(double interval){ clock.SetDelay(interval); }

	/**
	 * @brief �A�j���[�V�����̃C���f�b�N�X��ݒ肵�܂�
	 */
	void SetIndex(int i) { index = i; }
};

/**
 * @class Animator
 * @brief �A�j���[�^�[�N���X
 *
 * ���̃N���X�́A�A�j���[�V�����̍Đ���Ǘ����s���܂��B
 * �A�j���[�V�����̍Đ��𐧌䂵�A�A�j���[�V�����̐؂�ւ����s���܂��B
 */
class Animator final : public Component
{
private:
	//! �A�j���[�V�����̔z��
	std::unordered_map<std::string, Animation&> animations;

	//! ���ݍĐ����̃A�j���[�V����
	Animation* aniNode = nullptr;

	//! �����_���[
	class SpriteRenderer* rendererAttached = nullptr;

public:
	virtual void Update(float DeltaTime) override;

	/**
	 * @brief �A�j���[�V�����̓o�^
	 *
	 * �w�肳�ꂽ�A�j���[�V������o�^���܂��B
	 *
	 * @param name �A�j���[�V�����̖��O
	 * @param ani �o�^����A�j���[�V����
	 */
	void Insert(std::string name,Animation& ani);


	Animation* GetNode()const {return aniNode; }

	/**
	 * @brief �A�j���[�V�����̐؂�ւ�
	 *
	 * �w�肳�ꂽ�A�j���[�V�����ɐ؂�ւ��܂��B
	 *
	 * @param nodeName �؂�ւ���A�j���[�V�����̖��O
	 */
	void SetNode(std::string nodeName);

	void SetCalled(bool called);
};

#endif // !_ANIMATOR_H_

