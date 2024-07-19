/**
 * @file Debug.h
 * @brief �J���p�̃f�o�b�O�@�\��񋟂���N���X
 *
 * ���̃t�@�C���ɂ́A�J���p�̃f�o�b�O�@�\��񋟂���Debug�N���X����`����Ă��܂��B
 *
 * @date 2024/07/19
 * @author �T�g�E
 */


#ifndef _DEBUG_H_
#define _DEBUG_H_


struct Vertex
{
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

/**
 * @class Debug
 * @brief �J���p�̃f�o�b�O�@�\��񋟂���N���X
 *
 * Debug�N���X�́A�J���p�̃f�o�b�O�@�\��񋟂��܂��B
 * ��ɁA����l�p�`�A�~�Ȃǂ̐}�`��`�悷�邽�߂̃��\�b�h����������Ă��܂��B
 */
class Debug
{
public:
	
	/**
	 * @brief �f�o�b�O�p�̐���`�悵�܂�
	 */
	static void DrawLine(Vector2 start, Vector2 end, D3DCOLOR color);
	/**
	 * @brief �f�o�b�O�p�̎l�p�`��`�悵�܂�
	 */
	static void DrawBox(Vector2 pos, Vector2 size, D3DCOLOR color);
	/**
	 * @brief �f�o�b�O�p�̉~��`�悵�܂�
	 */
	static void DrawCircle(Vector2 pos, float radius, int segments, D3DCOLOR color);
};


#endif // !_DEBUG_H_