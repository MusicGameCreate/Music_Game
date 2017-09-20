//***********************************************************************************************************
//
// リザルトシーンクラス
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Result_Scene.h"

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
Result_Scene::Result_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr) : CBaseScene(changer)
{
	// ここでオブジェクトのnew処理
	mPlayDataMgr = datamgr;

	Background		= new Result_Background;
	Frame			= new Result_Frame;
	NowScore		= new Result_NowScore( mPlayDataMgr->GetPlayData(eData_Score) );
	HiScore			= new Result_HiScore;
	Jacket			= new Result_Jacket;
	DifficultType	= new Result_DifficultType( 1 );
	DifficultLevel	= new Result_DifficultLevel(18);
	MaxComboNum		= new Result_MaxComboNum( mPlayDataMgr->GetPlayData( eData_NowCombo ) );
	BCWGauge		= new Result_BCWGauge;
	Circuit			= new Result_Circuit;
	TitleFont		= new Result_TitleFont(L"初音ミクの消失", 7);	// 文字列、文字数
	ComposerName	= new Result_ComposerName(L"Cosmo@暴走P", 9);
	ClearGaugeNum	= new Result_ClearGaugeNum( 57 );



	ResultBGM = new CSound;
	ResultBGM->Init("../DATA/BGM/Main.wav");
	int playTime = ResultBGM->GetSoundFileLength();
	ResultBGM->SetCurrentPosition((float)playTime / 2.0f);
	ResultBGM->Play(true);
	double time = ResultBGM->GetNowPlayTime();
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
Result_Scene::~Result_Scene(void)
{
	// ここでオブジェクトのdelete処理
	delete Background;
	delete Frame;
	delete NowScore;
	delete HiScore;
	delete Jacket;
	delete DifficultType;
	delete DifficultLevel;
	delete MaxComboNum;
	delete BCWGauge;
	delete Circuit;
	delete TitleFont;
	delete ComposerName;
	delete ClearGaugeNum;

	ResultBGM->Stop();
	delete ResultBGM;

}

void Result_Scene::Initialize()
{

}

void Result_Scene::Finalize()
{

}

//***********************************************************************************************************
// 更新
//***********************************************************************************************************
void Result_Scene::Update(void)
{
	// ここでオブジェクトのupdate処理
	Background->Update();
	Frame->Update();
	NowScore->Update();
	HiScore->Update();
	Jacket->Update();
	DifficultType->Update();
	DifficultLevel->Update();
	MaxComboNum->Update();
	BCWGauge->Update();
	Circuit->Update();
	TitleFont->Update();
	ComposerName->Update();
	ClearGaugeNum->Update();

	if (CInput::GetKeyboardData(DIK_RETURN, TRIGGER))
	{
		mSceneChanger->ChangeScene(eScene_MusicSelect);
	}
}

//***********************************************************************************************************
// 描画
//***********************************************************************************************************
void Result_Scene::Draw(void)
{
	// 描画順は上の行から順に(但し2Dベース画像はこの限りではありません)
	Background->Draw();		// 背景色
	Circuit->Draw();		// 背景・回路
	Frame->Draw();			// 情報枠
	NowScore->Draw();		// 現在スコア
	HiScore->Draw();		// 過去最高スコア
	Jacket->Draw();			// プレイ曲ジャケット
	DifficultType->Draw();	// 難易度文字
	DifficultLevel->Draw();	// 難易度レベル
	MaxComboNum->Draw();	// 最大コンボ数
	BCWGauge->Draw();		// ボタン・クリック・ホイールゲージ
	TitleFont->Draw();		// 曲タイトル
	ComposerName->Draw();	// 作曲者名
	ClearGaugeNum->Draw();	// クリアゲージ数字

}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************