//***********************************************************************************************************
//
// ゲームシーン一括管理
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
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
// クラス定義
//***********************************************************************************************************
class GameMain_Scene : public CBaseScene
{
private:
	// オブジェクトはここで
	//*******************************************************************************************************
	GameMain_Background*		Background;			//
	GameMain_MusicDataFrame*	Music_Frame;		//	
	GameMain_MusicFrameBack*	Music_FrameBack;	//
	GameMain_Score*				Score;				// スコア数字
	GameMain_ScoreFont*			ScoreFont;			// スコア文字
	GameMain_Level*				Level;				// レベル数字
	GameMain_LevelFont*			LevelFont;			// レベル文字
	GameMain_MaxCombo*			MaxCombo;			// 最大コンボ文字
	GameMain_MaxComboFont*		MaxComboFont;		// 最大コンボ数字
	GameMain_BPMFont*			BPMFont;			// BPM文字
	GameMain_BPM*				BPM;				// BPM数字
	GameMain_HoiruButton*		HoiruButton;
	GameMain_PushEffect*		PushEffect;
	GameMain_JacketImage*		JacketImage;
	GameMain_Bar*				Bar;
	GameMain_HiSpeed*			HiSpeed;
	CTimeServer*				TimeServer;

	//Model_Template* Yuka;
	CLane*						Lane;
	CNotesMgr*					NotesMgr;

	IPlayDataMgr*				mPlayDataMgr;	// クラス間でデータを受け渡す

	CMusicDataReader			reader;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(void) override;	// 更新
	void Draw(void) override;	// 描画

	GameMain_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr);				// コンストラクタ
	virtual ~GameMain_Scene(void) override;		// デストラクタ
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************