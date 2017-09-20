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

//*************************************************************************
// �񋓑̒�`
//*************************************************************************

// �ȃZ���N�g��ʂɂĎg�p
//*************************************************
typedef enum
{
	LEFT_DOWN,			// �����ړ�
	RIGHT_DOWN,			// �E���ړ�
	LEFT_UP,			// ����ړ�
	RIGHT_UP,			// �E��ړ�
}MOVE_POSITION;

//*************************************************************************
// �\���̒�`
//*************************************************************************



// �g�̈ړ������A�`�揇�܂Ƃ�
//*************************************************
typedef struct
{
	int nMove_Vec_Up;	// ��̈ړ�����
	int nMove_Vec_Down;	// ���̈ړ�����
	int nDraw_Order;	// �`�揇
}OBJECT_MOVE_VEC;

//*************************************************************************
// �N���X��`
//*************************************************************************
class MusicSelect_RightFrame : public CTexture_2D_Base
{
private:
	OBJECT_MOVE_VEC		Move_Vec[7];			// �ړ����鎞�̈ړ�����


	const D3DXVECTOR3 MOVE_POSITION					= D3DXVECTOR3(  190.0f, 115.0f, 0.0f);	// �I�u�W�F�N�g���ړ�����ۂ̈ړ�����
	const D3DXVECTOR3 RIMIT_POSITION_UP				= D3DXVECTOR3( 1530.0f, -90.0f, 0.0f);	// �I�u�W�F�N�g���W�̏��
	const D3DXVECTOR3 POSITION_CENTER_UP_SPEAR		= D3DXVECTOR3( 1340.0f,  20.0f, 0.0f);	// �I�u�W�F�N�g��X�y�A���W
	const D3DXVECTOR3 POSITION_CENTER_UP_UP			= D3DXVECTOR3( 1150.0f, 135.0f, 0.0f);	// �I�u�W�F�N�g�Z���^�[2����W
	const D3DXVECTOR3 POSITION_CENTER_UP			= D3DXVECTOR3(  960.0f, 250.0f, 0.0f);	// �I�u�W�F�N�g�Z���^�[1����W
	const D3DXVECTOR3 POSITION_CENTER				= D3DXVECTOR3(  770.0f, 365.0f, 0.0f);	// �I�u�W�F�N�g�Z���^�[���W
	const D3DXVECTOR3 POSITION_CENTER_DOWN			= D3DXVECTOR3(  960.0f, 480.0f, 0.0f);	// �I�u�W�F�N�g�Z���^�[1�����W
	const D3DXVECTOR3 POSITION_CENTER_DOWN_DOWN		= D3DXVECTOR3( 1150.0f, 595.0f, 0.0f);	// �I�u�W�F�N�g�Z���^�[2�����W
	const D3DXVECTOR3 POSITION_CENTER_DOWN_SPEAR	= D3DXVECTOR3( 1340.0f, 710.0f, 0.0f);	// �I�u�W�F�N�g���X�y�A���W
	const D3DXVECTOR3 RIMIT_POSITION_DOWN			= D3DXVECTOR3( 1530.0f, 825.0f, 0.0f);	// �I�u�W�F�N�g���W�̉���	

	void Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum);

public:
	void Update( int DIFFICULT, bool UP, bool DOWN );
	int  Draw(int NUMBER);

	MusicSelect_RightFrame(void);
	virtual ~MusicSelect_RightFrame(void);
};

//*************************************************************************
// EOF
//*************************************************************************
