//***********************************************************************************************************
//
// �ȃZ���N�g�V�[���ꊇ�Ǘ�
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "BaseScene.h"
#include "IPlayDataMgr.h"
#include "MusicSelect_BackGround.h"
#include "MusicSelect_BackEffect.h"
#include "MusicSelect_LeftFrame.h"

#include "MusicSelect_RightFrame.h"
#include "MusicSelect_Score.h"
#include "MusicSelect_BPM.h"
#include "MusicSelect_Illustrator.h"
#include "MusicSelect_Creator.h"

#include "MusicSelect_RightFrame.h"
#include "MusicSelect_Jacket.h"
#include "MusicSelect_Level.h"


#include "CMusic_Manager.h"
#include "MusicDataReader.h"

typedef struct
{
	MusicData	Music_Data;			// �ȃf�[�^�̂قƂ��
	int			Hi_Score[3];		// �e��Փx�n�C�X�R�A
	int			Difficult_Level[3];	// �e��Փx���x��
	int			Clear_Mark[3];		// �e��Փx�N���A�}�[�N���
	int			Button_Rate[3];		// �e��Փx�{�^������
	int			Click_Rate[3];		// �e��Փx�N���b�N����
	int			Wheel_Rate[3];		// �e��Փx�z�C�[������

}MUSICSELECT_ALL_DATA;

//***********************************************************************************************************
// �N���X��`
//***********************************************************************************************************
class MusicSelect_Scene : public CBaseScene
{
private:
	// �I�u�W�F�N�g�͂�����
	MusicSelect_BackGround*		BackGround;
	MusicSelect_BackEffect*		BackEffect;
	MusicSelect_LeftFrame*		LeftFrame;

	MusicSelect_Score*			Score;
	MusicSelect_BPM*			BPM;
	MusicSelect_Illustrator*	Illustrator;
	MusicSelect_Creator*		Creator;

	MusicSelect_RightFrame*		RightFrame;			// �t���[��
	MusicSelect_Jacket*			Jacket;				// �W���P�b�g
	MusicSelect_Level*			Level;				// �e��Փx���x��

	CMusicDataReader			Reader;
	MUSICSELECT_ALL_DATA*		M_Data;

	int							nSelect_Data;		// ���ݑI�𒆂̋ȃf�[�^
	int							nNow_Difficult;		// ���ݓ�Փx
	bool						bMove_Up;			// ��ړ��t���O
	bool						bMove_Down;			// ���ړ��t���O
	int							nFrame_Count;
	bool						bData_Change_Flg;	// �f�[�^�ύX�^�C�~���O

	IPlayDataMgr*				mPlayDataMgr;
public:

	void Initialize();
	void Finalize();
	void Update(void);			// �X�V
	void Draw(void);				// �`��

	MusicSelect_Scene(ISceneChanger* changer, IPlayDataMgr* dataMgr);			// �R���X�g���N�^
	~MusicSelect_Scene(void) override;	// �f�X�g���N�^

};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************