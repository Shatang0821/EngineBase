/**
 * @file ResourceManager.h
 * @brief ���\�[�X�Ǘ��N���X�̒�`
 *
 * ���̃t�@�C���ɂ́AResourceManager�N���X����`����Ă��܂��B
 * ResourceManager�N���X�́A�Q�[�����Ŏg�p���郊�\�[�X�i�摜�Ȃǁj���Ǘ����܂��B
 * ��̓I�ɂ́A���\�[�X�̓ǂݍ��݁A�������A�A�N�Z�X���s���܂��B
 *
 * @date 2024/06/28
 * @author �T�g�E
 */
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "Singleton.h"
#include "MyTexture.h"
 /**
  * @enum ResID
  * @brief ���\�[�XID��\���񋓌^
  *
  * �Q�[�����Ŏg�p���郊�\�[�X����ӂɎ��ʂ��邽�߂�ID���`���܂��B
  */
enum class ResID
{
	Tex_Bullet,//��
};

/**
 * @class ResourceManager
 * @brief ���\�[�X�Ǘ��N���X
 *
 * ���̃N���X�́A�Q�[�����Ŏg�p���郊�\�[�X���Ǘ����܂��B
 * ��̓I�ɂ́A���\�[�X�̓ǂݍ��݁A�������A�A�N�Z�X���s���܂��B
 */
class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
protected:
	/**
	 * @brief �R���X�g���N�^
	 *
	 * �V���O���g���p�^�[�����ێ����邽�߂�protected�ɂ��Ă��܂��B
	 */
	ResourceManager() {};
	/**
	 * @brief �f�X�g���N�^
	 *
	 * �V���O���g���p�^�[�����ێ����邽�߂�protected�ɂ��Ă��܂��B
	 */
	~ResourceManager() {};
private:
	//! �摜���\�[�X�̃v�[��
	std::map<ResID, MyTexture*>imagePool;
	/**
	 * @brief ���\�[�X��ǂݍ���
	 *
	 * �w�肳�ꂽ���\�[�XID�ƃt�@�C���p�X�Ɋ�Â��āA�摜���\�[�X��ǂݍ��݂܂��B
	 *
	 * @param id ���\�[�XID
	 * @param pFname ���\�[�X�t�@�C���̃p�X
	 */

	void LoadTex(IDirect3DDevice9* pDev,ResID id,const TCHAR* pFname);
public:
	/**
	 * @brief ���\�[�X�}�l�[�W���̏�����
	 *
	 * �K�v�ȃ��\�[�X�����ׂď��������A�ǂݍ��݂܂��B
	 */
	void Initalize();
	/**
	 * @brief �w�肳�ꂽ���\�[�XID�ɑΉ�����e�N�X�`�����擾����
	 *
	 * �w�肳�ꂽ���\�[�XID�ɑΉ�����MyTexture�I�u�W�F�N�g���擾���܂��B
	 * ���\�[�X�����݂��Ȃ��ꍇ��nullptr��Ԃ��܂��B
	 *
	 * @param id ���\�[�XID
	 * @return �w�肳�ꂽ���\�[�XID�ɑΉ�����MyTexture�I�u�W�F�N�g�̃|�C���^
	 */
	MyTexture* Fetch(ResID id);
};

#endif // !_RESOURCEMANAGER_H_


