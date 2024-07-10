/**
 * @file Controller.h
 * @brief ���̓R���|�[�l���g���Ǘ�����N���X
 *
 * @author �T�g�E
 * @date 2024/06/30
 */
#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include "Component.h"

/**
 * @enum InputType
 * @brief ���͂̎�ނ�\���񋓌^
 *
 * ���͂������ꂽ�A�����ꂽ�A����������ꂽ��Ԃ�\���܂��B
 */
enum InputType
{
	Pressed,   ///< ���͂������ꂽ���
	Released,  ///< ���͂������ꂽ���
	Holding    ///< ���͂�����������ꂽ���
};

/**
 * @struct KeyBindInfo
 * @brief �L�[�o�C���h����ێ�����\����
 *
 * ���͂ɑ΂���R�[���o�b�N�֐��Ɠ��͂̎�ށA������Ă��邩�̏�Ԃ�ێ����܂��B
 */
struct KeyBindInfo
{
	std::function<void()> func; ///< �R�[���o�b�N�֐�
	InputType type; ///< ���͂̎��
	bool isPressed = false; ///< ���͂�������Ă��邩�ǂ����̏��
};

/**
 * @class InputComponent
 * @brief ���͂��Ǘ�����R���|�[�l���g�N���X
 *
 * ���̃N���X�́A���͂̃}�b�s���O�ƃo�C���f�B���O���Ǘ����A�Ή�����A�N�V���������s���܂��B
 * Component�N���X�����N���X�Ƃ��Čp�����Ă��܂��B
 */
class InputComponent : public Component
{
public:
	/**
	 * @brief ���̓}�b�s���O��ݒ肷��
	 *
	 * ���͖��ƒl��Ή��t���ē��̓}�b�s���O��ݒ肵�܂��B
	 *
	 * @param mappingName �}�b�s���O������̖͂��O
	 * @param code ���̓L�[�̒l
	 */
	void SetMapping(std::string mappingName, BYTE code);
	/**
	 * @brief �A�N�V�����ɑ΂�����̓o�C���f�B���O��ݒ肷��e���v���[�g�֐�
	 *
	 * �w�肵���A�N�V�������Ɠ��̓^�C�v�ɑ΂��āA�I�u�W�F�N�g�̃����o�֐����o�C���h���܂��B
	 *
	 * @tparam T �N���X�̌^
	 * @param actionName �A�N�V������
	 * @param type ���͂̎��
	 * @param obj �I�u�W�F�N�g�̃|�C���^
	 * @param func �o�C���h���郁���o�֐�
	 */
	template<typename T>
	void BindAction(std::string actionName, InputType type,T*obj,void(T::*func)()) {
		if (mappings.find(actionName) != mappings.end()) {
			callbacks.insert({ actionName,KeyBindInfo{std::bind(func,obj),type ,false} });
		}
	}
	/**
	 * @brief ���͂̍X�V���s��
	 *
	 * �t���[�����Ƃɓ��͂̏�Ԃ��X�V���A�Ή�����A�N�V���������s���܂��B
	 *
	 * @param DeltaTime �t���[���Ԃ̌o�ߎ���
	 */
	virtual void Update(float DeltaTime) override;
private:
	//! ���̓}�b�s���O
	std::map<std::string, BYTE>mappings;
	//! ���͂ɑ΂���R�[���o�b�N
	std::map<std::string, KeyBindInfo>callbacks;
};

#endif // !_INPUTCOMPONENT_H_


