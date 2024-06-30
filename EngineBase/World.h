/**
 * @file World.h
 * @brief �Q�[���S�ʂ��Ǘ�����N���X
 *
 * @author �T�g�E
 * @date 2024/06/21
 */
#ifndef _WORLD_H_
#define _WORLD_H_

#include "Object.h"
#include "Level.h"
#include "GameInstance.h"
#include "VisualInterface.h"
#include "CTimer.h"
#include "Controller.h"
#include "Camera.h"
 /**
  * @struct LayerSort
  * @brief LayerInterface�|�C���^���\�[�g���邽�߂̔�r�t�@���N�^
  *
  * ���̍\���̂́ALayerInterface�|�C���^�����̊�Ń\�[�g���邽�߂�
  * ��r�֐��I�u�W�F�N�g���`���܂��B���std::set�̃\�[�g���K�v�ȃR���e�i�Ŏg�p����܂��B
  */
struct LayerSort
{
	/**
	 * @brief ��r���Z�q
	 *
	 * ���̊֐��́A2��LayerInterface�|�C���^���r���A
	 * �\�[�g���������肵�܂��B��̓I�ɂ́A�܂�Layer�̒l���r���A
	 * �l�������ꍇ�ɂ̓|�C���^�̃A�h���X���r���ă\�[�g���������肵�܂��B
	 *
	 * @param a ��r�Ώۂ̍ŏ���LayerInterface�|�C���^
	 * @param b ��r�Ώۂ�2�Ԗڂ�LayerInterface�|�C���^
	 * @return a��b���O�ɂ���ꍇ��true�A�����łȂ��ꍇ��false
	 */
	bool operator()(const class LayerInterface* a, const class LayerInterface* b) const {
		if (a->GetLayer() == b->GetLayer())
			return a < b;
		else
			return a->GetLayer() < b->GetLayer();
	}
};


 /**
  * @class World
  * @brief �Q�[�����Ǘ�����N���X
  *
  * @details ���̃N���X�́A
  * �Q�[�����̃^�C�}�[�AUI�A�V�[���I�u�W�F�N�g���Ǘ�����N���X
  * 
  */
class World final
{
	friend class Engine;
	friend class GameStatics;
	friend class Timer;
	friend class LayerInterface;
	friend class Camera;
	friend class SpriteRenderer;

	friend void Object::Destroy();
private:
	/* �V�[���I�u�W�F�N�g�AUI�A�^�C�}�[�R���e�i*/

	//! �I�u�W�F�N�g�R���e�i
	std::set<class Object*>GameObjects;
	//! �폜�\��̃I�u�W�F�N�g�R���e�i
	std::set<class Object*>GameObjects_to_delete;

	//! UI�R���e�i
	std::set<class UserInterface*>GameUIs;
	//! �폜�\���UI�R���e�i
	std::set<class UserInterface*>GameUIs_to_delete;

	//! �^�C�}�[�R���e�i
	std::set<class Timer*>GameTimers;

	/* �����_���[�A�R���C�_�[�R���e�i*/

	//! �����_���[�R���e�i
	std::set<class LayerInterface*,LayerSort>GameRenderers;
	//! �R���C�_�[�R���e�i
	std::set<class BoxCollider*>GameColliders;	//�܂��{�b�N�X������
	//             Circle�����\��

	/*�Q�[���V���O���g���I�u�W�F�N�g*/

	//! �V�[�����w���C���X�^���X
	Level* currentLevel = nullptr;
	//! ���͂Əo�͊Ǘ�
	class Controller* mainController = nullptr;
	//! �Q�[���f�[�^�Ǘ�
	GameInstance* gameInstance = nullptr;
	//! ���C���J����
	class Camera* mainCamera = nullptr;

	/*  FPS�֘A  */

	float deltaTime = 0.016f;			// �O�t���[������̌o�ߎ���.
	float fixedDeltaTime = 0.02f;		// �Œ�Ԋu

	float fixedAccumulator = 0;		//�o�ߎ���

	UINT fps = 0;

	CTimer Timer;			// ���ԊǗ��I�u�W�F�N�g(Update�p).

private:
	/* ���C�����W�b�N */

	/**
	 * @brief �Q�[���X�V����
	 *
	 * ���̊֐��́A�Q�[���̏�Ԃ��X�V���܂��B
	 *
	 * @param DeltaTime �O�t���[������̌o�ߎ���
	 */
	void Update(float DeltaTime);

	/**
	 * @brief �Q�[�������X�V����
	 *
	 * ���̊֐��́A�Q�[���̕�����Ԃ��X�V���܂��B
	 *
	 */
	void FixedUpdate();

	/**
	 * @brief �Q�[���`��X�V����
	 *
	 * ���̊֐��́A�Q�[���̕`����X�V���܂��B
	 */
	void Render();

	/**
	 * @brief ���͍X�V����
	 *
	 * ���̊֐��́A�Q�[���̓��͂��X�V���܂��B
	 */
	void Input();

};

extern World mainWorld;
#endif // !_WORLD_H_



