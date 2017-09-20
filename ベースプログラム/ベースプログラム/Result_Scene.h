//***********************************************************************************************************
//
// リザルトシーン一括管理
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
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
// クラス定義
//***********************************************************************************************************
class Result_Scene : public CBaseScene
{
private:
	// オブジェクトはここで
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



	IPlayDataMgr*	mPlayDataMgr;	// クラス間でデータを受け渡す
	CSound*			ResultBGM;

public:
	void Initialize();
	void Finalize();
	void Update(void);				// 更新
	void Draw(void);					// 描画

	Result_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr);	// コンストラクタ
	virtual	~Result_Scene(void) override;			// デストラクタ

};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************