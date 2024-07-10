/**
 * @file myTexture.h
 * @brief �e�N�X�`���[�Ǘ��N���X
 *
 * ���̃t�@�C���ɂ́ADirect3D���g�p���ăe�N�X�`�����Ǘ����邽�߂�
 * MyTexture�N���X����`����Ă��܂��B�e�N�X�`���̓ǂݍ��݁A�擾�A
 * �j�����ȒP�ɍs�����߂̃C���^�[�t�F�[�X��񋟂��܂��B
 *
 * @date 2024/06/28
 * @author �T�g�E
 */

#ifndef _MYTEXTURE_H_
#define _MYTEXTURE_H_


//! �Ǘ�����ő�e�N�X�`����
const int MAX_TEXTURE = 256;

/**
 * @class MyTexture
 * @brief �e�N�X�`���[�Ǘ��N���X
 *
 * ���̃N���X�́ADirect3D�e�N�X�`�����Ǘ����A�e�N�X�`���̓ǂݍ��݁A
 * �擾�A�j�����s���܂��B�V���O���g���p�^�[�����g�p���ĕ����̃e�N�X�`��
 * ���Ǘ����܂��B
 */
class MyTexture
{
private: 
	//! �e�N�X�`���Ǘ��X�^�b�N
	static MyTexture* sm_pStack[MAX_TEXTURE];
	//! �Ǘ�����e�N�X�`���̐�
	static int sm_maxTexture;

protected:
	//! �Ǘ�����e�N�X�`��
	IDirect3DTexture9* m_pTex;
	//! �e�N�X�`���̕�
	int m_width;
	//! �e�N�X�`���̍���
	int m_height;
private:
	/**
	* @brief �R���X�g���N�^
	*
	* MyTexture�N���X�̃C���X�^���X�����������܂��B
	* �e�N�X�`���|�C���^m_pTex��NULL�ŏ��������܂��B
	*/
	MyTexture() 
	: m_pTex(NULL)
	, m_width(0)
	, m_height(0)
	{
	}
	/**
	 * @brief �f�X�g���N�^
	 *
	 * MyTexture�N���X�̃C���X�^���X��j�����܂��B
	 * �Ǘ�����e�N�X�`����������܂��B
	 */
	virtual ~MyTexture()
	{
		if (m_pTex)
		{
			m_pTex->Release();
		}
	}
public:
	/**
	 * @brief �e�N�X�`�����擾����
	 *
	 * �e�N�X�`���|�C���^��Ԃ��܂��B
	 *
	 * @return �e�N�X�`���|�C���^
	 */
	IDirect3DTexture9* GetTexture()
	{
		return m_pTex;
	}

	/**
	 * @brief �e�N�X�`���̕����擾����
	 *
	 * ����Ԃ��܂��B
	 *
	 * @return ��
	 */
	int GetWidth() const { return m_width; }
	/**
	 * @brief �e�N�X�`���̍������擾����
	 *
	 * ������Ԃ��܂��B
	 *
	 * @return ����
	 */
	int GetHeight() const { return m_height; }

	/**
	 * @brief �e�N�X�`����ǂݍ���
	 *
	 * MyTexture�I�u�W�F�N�g���쐬���A�w�肳�ꂽ�t�@�C������e�N�X�`����ǂݍ��݂܂��B
	 *
	 * @param pDev Direct3D�f�o�C�X
	 * @param pFname �e�N�X�`���t�@�C����
	 * @return MyTexture�I�u�W�F�N�g�̃|�C���^
	 */
	static MyTexture* LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname);

	/**
	 * @brief �X�v���C�g���쐬����
	 *
	 * �X�v���C�g�V�[�g����w�肳�ꂽ�̈�̃X�v���C�g���쐬���܂��B
	 *
	 * @param pDev Direct3D�f�o�C�X
	 * @param pFname �X�v���C�g�V�[�g�̃t�@�C����
	 * @param u1 �X�v���C�g�̍����U���W
	 * @param v1 �X�v���C�g�̍����V���W
	 * @param u2 �X�v���C�g�̉E����U���W
	 * @param v2 �X�v���C�g�̉E����V���W
	 * @return MyTexture�I�u�W�F�N�g�̃|�C���^
	 */
	static MyTexture* CreateSprite(IDirect3DDevice9* pDev, const TCHAR* pFname, float u1, float v1, float u2, float v2);

	/**
	 * @brief �S�Ẵe�N�X�`����j������
	 *
	 * �ǂݍ��񂾑S�Ẵe�N�X�`����j�����܂��B
	 */
	static void ReleaseAll();
};

/**
 * @brief �e�N�X�`����ǂݍ��ރw���p�[�֐�
 *
 * �w�肳�ꂽ�t�@�C������Direct3D�e�N�X�`����ǂݍ��݂܂��B
 *
 * @param pDev Direct3D�f�o�C�X
 * @param pFname �e�N�X�`���t�@�C����
 * @param ppTex �ǂݍ��񂾃e�N�X�`���|�C���^�ւ̃|�C���^
 * @return HRESULT ���������ꍇ��S_OK�A���s�����ꍇ�̓G���[�R�[�h
 */
HRESULT LoadTexture(IDirect3DDevice9* pDev, const TCHAR* pFname, IDirect3DTexture9** ppTex);
#endif // !_MYTEXTURE_H_
