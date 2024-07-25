/**
 * @file World.h
 * @brief �Q�[���S�ʂ��Ǘ�����World�N���X�̒�`���܂ރw�b�_�t�@�C���B
 *
 * World�N���X�́A�Q�[�����̃I�u�W�F�N�g�AUI�A�^�C�}�[�A�����_���[�A�R���C�_�[�Ȃǂ��Ǘ����܂��B
 * �܂��A�Q�[���̃��C�����[�v�ɂ�����X�V�A���������A�`�揈����S�����܂��B
 *
 * @author �T�g�E
 * @date 2024/06/21
 */
#ifndef _WORLD_H_
#define _WORLD_H_

#include "Object.h"
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
 * @struct ColliderSort
 * @brief Collider�I�u�W�F�N�g���\�[�g���邽�߂̔�r�t�@���N�^�B
 *
 * Collider�I�u�W�F�N�g�����C���[�Ɋ�Â��ă\�[�g���邽�߂Ɏg�p����܂��B
 * �������C���[�̏ꍇ�́A�|�C���^�̃A�h���X�Ŕ�r���܂��B
 */
struct ColliderSort
{
	bool operator()(const class Collider* a, const class Collider* b) const;
};


/**
* @class World
* @brief �Q�[���̃��C�����[�v�ƃI�u�W�F�N�g�Ǘ���S������N���X�B
*
* �Q�[�����̃I�u�W�F�N�g�AUI�A�^�C�}�[�A�����_���[�A�R���C�_�[�̊Ǘ����s���܂��B
* Init�ŏ��������s���AUpdate�ŃQ�[���̏�Ԃ��X�V�AFixedUpdate�ŕ����������s���A
* Render�ŕ`�揈�����s���܂��BInput�œ��͏������s���ADebug�Ńf�o�b�O����\�����܂��B
*/
class World final
{
	friend class MyApp;
	friend class Debug;
	friend class GameStatics;
	friend class Timer;
	friend class Controller;
	friend class LayerInterface;
	friend class Camera;
	friend class SpriteRenderer;
	friend class Collider;
	friend class CircleCollider;
	friend class BoxCollider;

	friend void Object::Destroy();
private:
	/* �V�[���I�u�W�F�N�g�AUI�A�^�C�}�[�R���e�i*/

	//! �I�u�W�F�N�g�R���e�i
	std::unordered_set<class Object*>GameObjects;
	//! �폜�\��̃I�u�W�F�N�g�R���e�i
	std::unordered_set<class Object*>GameObjects_to_delete;

	//! UI�R���e�i
	std::unordered_set<class UserInterface*>GameUIs;
	//! �폜�\���UI�R���e�i
	std::unordered_set<class UserInterface*>GameUIs_to_delete;

	//! �^�C�}�[�R���e�i
	std::unordered_set<class Timer*>GameTimers;

	/* �����_���[�A�R���C�_�[�R���e�i*/

	//! �����_���[�R���e�i
	std::set<class LayerInterface*,LayerSort>GameRenderers;
	//! �R���C�_�[�R���e�i
	std::unordered_set<class Collider*>GameColliders;
	std::set<class Collider*, ColliderSort>ColliderZones[8][6];

	/*�Q�[���V���O���g���I�u�W�F�N�g*/

	//! �V�[�����w���C���X�^���X
	class Level* currentLevel = nullptr;
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
	 * @brief �Q�[������������
	 * 
	 */
	bool Init();
	
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
	void FixedUpdate(float fixedDeltaTime);

	/**
	 * @brief �����v�Z����
	 *
	 */
	void ProcessColliderZones();

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

	/**
	 * @brief �f�o�b�O�@�\
	 *
	 * ���̊֐��́A�f�o�b�O�@�\��񋟂��܂��B
	 */
	void Debug();
	
	/**
	 * @brief ���\�[�X�������
	 *
	 * ���̊֐��́A�Q�[���Ŏg�p�������\�[�X��������܂��B
	 */
	void ReleaseData();

public:

	class Camera* GetMainCamera() { return mainCamera; }
};

extern World mainWorld;

/**
 * @brief ���I�L���X�g���s���e���v���[�g�֐�
 *
 * ���̊֐��́A�^����ꂽBase�N���X�̃|�C���^���w�肳�ꂽ�^�ɑ΂��ē��I�L���X�g���s���܂��B
 * �L���X�g�����������ꍇ�A�w�肳�ꂽ�^�̃|�C���^��Ԃ��܂��B���s�����ꍇ��nullptr��Ԃ��܂��B
 *
 * @tparam T �L���X�g����^
 * @param pBase �L���X�g�Ώۂ�Base�N���X�̃|�C���^
 * @return T* �L���X�g���ꂽ�^�̃|�C���^�B�L���X�g�����s�����ꍇ��nullptr�B
 */
template<typename T>
T* Cast(Base* pBase)
{
	// pBase���L���ł���Γ��I�L���X�g���s���A���ʂ�Ԃ�
	if (pBase) {
		return dynamic_cast<T*>(pBase);
	}
	// pBase��nullptr�̏ꍇ��nullptr��Ԃ�
	std::cout << "Cast failed" << std::endl;
	return nullptr;
}
#endif // !_WORLD_H_



