//*************************************************************************
//
// �����ɃI�u�W�F�N�g�̐���
//
//*************************************************************************
#pragma once 

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "CTexture_2D_Base.h" 
#include "MusicSelect_RightFrame.h"

//*************************************************************************
// �\���̒�`
//*************************************************************************
typedef struct
{
	char*	Music_Jacket_Pass;	// �ȑS�W���P�b�g�p�X
	int		nTexture_Num;		// �e�N�X�`���ǂݍ��ݎ��ɐݒ肵���e�N�X�`���ԍ�

}JACKET_DATA;

//*************************************************************************
// �N���X��`
//*************************************************************************
class MusicSelect_Jacket : public CTexture_2D_Base
{
private:
	int					nAll_Music_Num;		// �ȑ���
	JACKET_DATA*		Jacket_Data;

	int					nCount;				// FPS�J�E���^
	int					nTexture;			// 

	bool				bMove_Up;			// ������Ɉړ����邩�ǂ���
	bool				bMove_Down;			// �������Ɉړ����邩�ǂ���

	OBJECT_MOVE_VEC		Move_Vec[7];		// �ړ����鎞�̈ړ�����
	int					nNow_SetTexture[7];	// ���݂̃I�u�W�F�N�g�ɃZ�b�g����Ă���e�N�X�`���̔ԍ�

	const D3DXVECTOR3 MOVE_POSITION					= D3DXVECTOR3(  195.0f,  110.0f, 0.0f );	// �I�u�W�F�N�g���ړ�����ۂ̈ړ�����
	const D3DXVECTOR3 RIMIT_POSITION_UP				= D3DXVECTOR3( 1375.0f,  -75.0f, 0.0f );	// �I�u�W�F�N�g���W�̏��
	const D3DXVECTOR3 POSITION_CENTER_UP_SPEAR		= D3DXVECTOR3( 1180.0f,   35.0f, 0.0f );	// �I�u�W�F�N�g��X�y�A���W
	const D3DXVECTOR3 POSITION_CENTER_UP_UP			= D3DXVECTOR3(  985.0f,  145.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[2����W
	const D3DXVECTOR3 POSITION_CENTER_UP			= D3DXVECTOR3(  790.0f,  255.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[1����W
	const D3DXVECTOR3 POSITION_CENTER				= D3DXVECTOR3(  595.0f,  365.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[���W
	const D3DXVECTOR3 POSITION_CENTER_DOWN			= D3DXVECTOR3(  790.0f,  475.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[1�����W
	const D3DXVECTOR3 POSITION_CENTER_DOWN_DOWN		= D3DXVECTOR3(  985.0f,  585.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[2�����W
	const D3DXVECTOR3 POSITION_CENTER_DOWN_SPEAR	= D3DXVECTOR3( 1180.0f,  695.0f, 0.0f );	// �I�u�W�F�N�g���X�y�A���W
	const D3DXVECTOR3 RIMIT_POSITION_DOWN			= D3DXVECTOR3( 1375.0f,  805.0f, 0.0f );	// �I�u�W�F�N�g���W�̉���

	void Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum);

public:
	void Update(bool UP, bool DOWN);
	void Draw(int NUMBER);

	MusicSelect_Jacket(void);
	virtual ~MusicSelect_Jacket(void);
};

//*************************************************************************
// EOF
//*************************************************************************
