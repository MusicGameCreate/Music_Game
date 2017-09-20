//*******************************************************************************************************
//
// 3D�摜�`���{�N���X
//
//*******************************************************************************************************
#pragma once

//*******************************************************************************************************
// �C���N���[�h��
//*******************************************************************************************************
#include "Define.h"
#include "CDirectX.h"	// DirectX���
#include "CInput.h"		// �L�[�{�[�h�A�}�E�X���
#include "CSound.h"		// �T�E���h���

#include "Camera.h"

#include "Debug_DataSave.h"

// �񋓌^
enum
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_CENTER,
};

//*******************************************************************************************************
// �\���̒�`
//*******************************************************************************************************
typedef struct
{
	D3DXMATRIX	mtxWorld;		// ���[���h�}�g���N�X
	D3DXMATRIX	mtxScale;		// �g�嗦
	D3DXMATRIX	mtxTranslate;	// ���s�ړ�
	D3DXMATRIX	mtxRot;			// ��]

	D3DXVECTOR3	Obj_Pos;		// ���W(�摜�̒��S�����_)
	D3DXVECTOR2	Obj_Size;		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
	D3DXVECTOR2	Tex_Pos;		// �e�N�X�`�����W(0.0f�`1.0f)
	D3DXVECTOR2	Tex_Anim;		// 1�A�j���[�V�������̃e�N�X�`�����W(1�A�j���[�V�����Ȃ�1.0f)
	int			Red;			// �摜��R�l
	int			Green;			// �摜��G�l
	int			Brue;			// �摜��B�l
	int			Alpha;			// �摜�̃A���t�@�l
	D3DXVECTOR3	Obj_Rot;		// ��]�p�x
	D3DXVECTOR3	Obj_Scale;		// �g�嗦

}TEXTURE_3D_DATA;

//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CTexture_3D_Base
{
	
	D3DXMATRIX				mtxView;			// �r���[�s��
	VERTEX_3D*				aVertex;			// ���_���i�[

protected:
	TEXTURE_3D_DATA*		Tex_3D_Data;		// �e�N�X�`�����܂Ƃߍ\����
	LPDIRECT3DTEXTURE9*		pTexture;			// �e�N�X�`���f�[�^�ւ̃|�C���^
	int						nObject_Num;		// �I�u�W�F�N�g�����������邩�H(��{��1�����Ă����Ă�������)
	int						nUse_Texture_Num;	// �e�N�X�`���͉��g�p���邩�H(��{��1�����Ă����Ă�������)

	bool					bBillboard;			// �r���{�[�h�ɂ��邩�ǂ����w��
	bool					bAlphaTest;			// ���e�X�g��K�p���邩�ǂ����w��

	bool					UseQuaternion;
	D3DXQUATERNION			q;					// �P�ʃN�H�[�^�j�I��'q'�𐶐�
	D3DXMATRIX				TurnMat;			// ��]�s��
	D3DXMATRIX				mat;				//���s�ړ��s��
	D3DXVECTOR3				NAxis;				// �C�ӂ̒��S��

	int						ScaleDirection;		// �g�k���̕���

private:
	void					MakeVertex();		// ���_��񏉊���
	void					SetVertex();		// ���_���X�V
	void					SetTexture();		// �e�N�X�`�����W���X�V
	void					SetColor();			// �e�N�X�`���J���[���X�V

public:	
	virtual void Init();										// ������
	virtual void Load_Texture(char* TEXTURE_FILE, int NUMBER);	// �e�N�X�`���ǂݍ���
	virtual void Finalise();									// �I��
	virtual void Update();										// �X�V
	virtual void Draw(int NUMBER, int SET_TEXTURE);				// �`��

	CTexture_3D_Base();											// �R���X�g���N�^
	virtual ~CTexture_3D_Base();								// �f�X�g���N�^
	
	void QuaternionRotate();
};

//*******************************************************************************************************
// EOF
//*******************************************************************************************************