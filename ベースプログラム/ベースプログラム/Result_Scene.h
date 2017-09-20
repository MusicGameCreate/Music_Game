//***********************************************************************************************************
//
// ���U���g�V�[���ꊇ�Ǘ�
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "BaseScene.h"
#include "Result_Background.h"
#include "Result_Frame.h"
#include "Result_NowScore.h"
#include "Result_HiScore.h"
#include "Result_Jacket.h"
#include "Result_DifficultLevel.h"
#include "Result_MaxComboNum.h"
#include "Result_BCWGauge.h"
#include "Result_Circuit.h"
#include "Result_DifficultType.h"
#include "Result_TitleFont.h"
#include "Result_ComposerName.h"
#include "Result_ClearGaugeNum.h"

#include "IPlayDataMgr.h"

//***********************************************************************************************************
// �N���X��`
//***********************************************************************************************************
class Result_Scene : public CBaseScene
{
private:
	// �I�u�W�F�N�g�͂�����
	Result_Background*		Background;
	Result_Frame*			Frame;
	Result_NowScore*		NowScore;
	Result_HiScore*			HiScore;
	Result_Jacket*			Jacket;
	Result_DifficultType*	DifficultType;
	Result_DifficultLevel*	DifficultLevel;
	Result_MaxComboNum*		MaxComboNum;
	Result_BCWGauge*		BCWGauge;
	Result_Circuit*			Circuit;
	Result_TitleFont*		TitleFont;
	Result_ComposerName*	ComposerName;
	Result_ClearGaugeNum*	ClearGaugeNum;



	IPlayDataMgr*	mPlayDataMgr;	// �N���X�ԂŃf�[�^���󂯓n��
	CSound*			ResultBGM;

public:
	void Initialize();
	void Finalize();
	void Update(void);				// �X�V
	void Draw(void);					// �`��

	Result_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr);	// �R���X�g���N�^
	virtual	~Result_Scene(void) override;			// �f�X�g���N�^

};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************