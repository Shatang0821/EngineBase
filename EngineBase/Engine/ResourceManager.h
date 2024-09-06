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
	Tex_Player_Idle,	//�v���C���[��
	Tex_Player_Run,		//�v���C���[��
	Tex_Player_Jump,	//�v���C���[��
	Tex_Player_Fall,	//�v���C���[��
};

//�A�j���[�V�������\�[�X
struct AnimationResource
{
	//�A�g���X
	std::vector<MyTexture*> texs;
	//�A�j���[�V�����̃t���[����
	int num;
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
private:
	//! �摜���\�[�X�̃v�[��
	std::unordered_map<ResID, MyTexture*>imagePool;
	std::unordered_map<ResID, AnimationResource>animPool;
	/**
	 * @brief �P���摜���\�[�X��ǂݍ���
	 *
	 * �w�肳�ꂽ���\�[�XID�ƃt�@�C���p�X�Ɋ�Â��āA�摜���\�[�X��ǂݍ��݂܂��B
	 *
	 * @param pDev Direct3D�f�o�C�X
	 * @param id ���\�[�XID
	 * @param pFname ���\�[�X�t�@�C���̃p�X
	 */
	bool LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname);

	/**
	 * @brief �������摜���\�[�X��ǂݍ���
	 *
	 * �w�肳�ꂽ���\�[�XID�ƃt�@�C���p�X�Ɋ�Â��āA�摜���\�[�X��ǂݍ��݂܂��B
	 *
	 * @param pDev Direct3D�f�o�C�X
	 * @param id ���\�[�XID
	 * @param pFname ���\�[�X�t�@�C���̃p�X.png�������Ȃ�
	 * @param num �摜�̖���
	 */
	bool LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname,int num);

	/**
	 * @brief �X�v���C�g�V�[�g�摜���\�[�X��ǂݍ���
	 *
	 * �w�肳�ꂽ���\�[�XID�ƃt�@�C���p�X�Ɋ�Â��āA�摜���\�[�X��ǂݍ��݂܂��B
	 *
	 * @param pDev Direct3D�f�o�C�X
	 * @param id ���\�[�XID
	 * @param pFname ���\�[�X�t�@�C���̃p�X
	 * @param num �摜�̖���
	 * @param row �摜�̍s��
	 * @param col �摜�̗�
	 * @param texWidth �摜�̕�
	 * @param texHeight �摜�̍���
	 */
	bool LoadTex(IDirect3DDevice9* pDev, ResID id, const TCHAR* pFname, int num, int row, int col, int texWidth, int texHeight);
	
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

public:
	/**
	 * @brief ���\�[�X�}�l�[�W���̏�����
	 *
	 * �K�v�ȃ��\�[�X�����ׂď��������A�ǂݍ��݂܂��B
	 * 
	 * @return ���������ꍇ��true�A���s�����ꍇ��false��Ԃ��܂��B
	 */
	bool Initalize();
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

	/**
	 * @brief �w�肳�ꂽ���\�[�XID�ɑΉ�����A�j���[�V�������\�[�X���擾����
	 *
	 * �w�肳�ꂽ���\�[�XID�ɑΉ�����A�j���[�V�������\�[�X���擾���܂��B
	 * ���\�[�X�����݂��Ȃ��ꍇ��nullptr��Ԃ��܂��B
	 *
	 * @param id ���\�[�XID
	 * @return �w�肳�ꂽ���\�[�XID�ɑΉ�����A�j���[�V�������\�[�X
	 */
	AnimationResource FetchAnim(ResID id);
};

#endif // !_RESOURCEMANAGER_H_


