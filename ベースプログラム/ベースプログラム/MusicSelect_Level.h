//*************************************************************************
//
// �ȃZ���N�g��ʁE�e��Փx���x��
//
//*************************************************************************
#pragma once 

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "CTexture_2D_Base.h" 
#include "MusicSelect_RightFrame.h"
#include "CMusic_Manager.h"

typedef struct
{
	int Easy_Level;
	int Hyper_Level;
	int Master_Level;
}MUSIC_LEVEL;

//*************************************************************************
// �N���X��`
//*************************************************************************
class MusicSelect_Level : public CTexture_2D_Base
{
private:
	int					nOver_UP;			// ���ݍŏ�ɂ���I�u�W�F�N�g�̐���
	int					nOver_DOWN;			// ���ݍŉ��ɂ���I�u�W�F�N�g�̐���
	bool				bOne_Flg;			// ����̂ݕύX��������Ƃ��Ɏg�p

	OBJECT_MOVE_VEC		Move_Vec[7];		// �ړ����鎞�̈ړ�����
	MUSIC_LEVEL*		All_Level;			// �S�ȓ�Փx���x��
	MUSIC_LEVEL			Music_Level[7];		// �e�Ȃɐݒ肷��ׂ����x��

	D3DXVECTOR3 MOVE_POSITION;				// �I�u�W�F�N�g���ړ�����ۂ̈ړ�����
	D3DXVECTOR3 RIMIT_POSITION_UP;			// �I�u�W�F�N�g���W�̏��
	D3DXVECTOR3 POSITION_CENTER_UP_SPEAR;	// �I�u�W�F�N�g��X�y�A���W
	D3DXVECTOR3 POSITION_CENTER_UP_UP;		// �I�u�W�F�N�g�Z���^�[2����W
	D3DXVECTOR3 POSITION_CENTER_UP;			// �I�u�W�F�N�g�Z���^�[1����W
	D3DXVECTOR3 POSITION_CENTER;			// �I�u�W�F�N�g�Z���^�[���W
	D3DXVECTOR3 POSITION_CENTER_DOWN;		// �I�u�W�F�N�g�Z���^�[1�����W
	D3DXVECTOR3 POSITION_CENTER_DOWN_DOWN;	// �I�u�W�F�N�g�Z���^�[2�����W
	D3DXVECTOR3 POSITION_CENTER_DOWN_SPEAR;	// �I�u�W�F�N�g���X�y�A���W
	D3DXVECTOR3 RIMIT_POSITION_DOWN;		// �I�u�W�F�N�g���W�̉���	

	void Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum, int Soezi);

public:
	void Update(bool UP, bool DOWN);
	void Draw(int NUM);

	void Set_Level( int LEVEL, int NUM, int DIFFICULT );

	MusicSelect_Level(void);
	virtual ~MusicSelect_Level(void);
};



//*************************************************************************
// EOF
//*************************************************************************
