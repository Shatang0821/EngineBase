/**
 * @file World.h
 * @brief �Q�[���S�ʂ��Ǘ�����N���X
 *
 * @author �T�g�E
 * @date 2024/06/21
 */
#ifndef _WORLD_H_
#define _WORLD_H_

#include <set>
#include "Object.h"
#include "Level.h"
#include "GameInstance.h"

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
	std::set<class LayerInterface*>GameRenderers;
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



