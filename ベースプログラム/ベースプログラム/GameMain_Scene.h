//***********************************************************************************************************
//
// �Q�[���V�[���ꊇ�Ǘ�
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "GameMain_Score.h"
#include "GameMain_MusicDataFrame.h"
#include "GameMain_MusicFrameBack.h"
#include "GameMain_HoiruButton.h"
#include "GameMain_ScoreFont.h"
#include "GameMain_Level.h"
#include "GameMain_LevelFont.h"
#include "GameMain_PushEffect.h"
#include "GameMain_Background.h"
#include "GameMain_MaxComboFont.h"
#include "GameMain_MaxCombo.h"
#include "GameMain_JacketImage.h"
#include "GameMain_BPMFont.h"
#include "GameMain_BPM.h"
#include "GameMain_Bar.h"
#include "GameMain_HiSpeed.h"
#include "TimeServer.h"

#include "Model_Template.h"
#include "Lane.h"
#include "NotesMgr.h"

#include "IPlayDataMgr.h"
#include "ISceneChanger.h"
#include "BaseScene.h"

//***********************************************************************************************************
// �N���X��`
//***********************************************************************************************************
class GameMain_Scene : public CBaseScene
{
private:
	// �I�u�W�F�N�g�͂�����
	//*******************************************************************************************************
	GameMain_Background*		Background;			//
	GameMain_MusicDataFrame*	Music_Frame;		//	
	GameMain_MusicFrameBack*	Music_FrameBack;	//
	GameMain_Score*				Score;				// �X�R�A����
	GameMain_ScoreFont*			ScoreFont;			// �X�R�A����
	GameMain_Level*				Level;				// ���x������
	GameMain_LevelFont*			LevelFont;			// ���x������
	GameMain_MaxCombo*			MaxCombo;			// �ő�R���{����
	GameMain_MaxComboFont*		MaxComboFont;		// �ő�R���{����
	GameMain_BPMFont*			BPMFont;			// BPM����
	GameMain_BPM*				BPM;				// BPM����
	GameMain_HoiruButton*		HoiruButton;
	GameMain_PushEffect*		PushEffect;
	GameMain_JacketImage*		JacketImage;
	GameMain_Bar*				Bar;
	GameMain_HiSpeed*			HiSpeed;
	CTimeServer*				TimeServer;

	//Model_Template* Yuka;
	CLane*						Lane;
	CNotesMgr*					NotesMgr;

	IPlayDataMgr*				mPlayDataMgr;	// �N���X�ԂŃf�[�^���󂯓n��

	CMusicDataReader			reader;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(void) override;	// �X�V
	void Draw(void) override;	// �`��

	GameMain_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr);				// �R���X�g���N�^
	virtual ~GameMain_Scene(void) override;		// �f�X�g���N�^
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************