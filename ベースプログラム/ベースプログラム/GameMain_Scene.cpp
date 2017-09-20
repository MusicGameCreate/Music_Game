//***********************************************************************************************************
//
// ゲームメインシーン一括管理
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "GameMain_Scene.h"
//#include <boost/thread.hpp>

//using namespace boost;

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
GameMain_Scene::GameMain_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr) : CBaseScene(changer)
{
	mPlayDataMgr = datamgr;
	//thread InitThread(bind(&GameMain_Scene::Initialize, this));

	//InitThread.join();

	ShowCursor(FALSE);
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
GameMain_Scene::~GameMain_Scene(void)
{
	// ここでオブジェクトのdelete処理
	delete Background;
	delete Score;
	delete ScoreFont;
	delete Music_Frame;
	delete Music_FrameBack;
	delete HoiruButton;
	delete Level;
	delete LevelFont;
	delete BPMFont;
	delete BPM;
	delete PushEffect;
	delete MaxCombo;
	delete MaxComboFont;
	delete JacketImage;
	delete Bar;
	delete HiSpeed;
	delete TimeServer;

	//delete Yuka;
	//delete Lane;
	delete NotesMgr;

	ShowCursor(TRUE);
}

void GameMain_Scene::Initialize()
{
	reader.JacketFileLoad("../DATA/MUSIC/LemonadeParty.music/lemon_E.score");
	// ここでオブジェクトのnew処理
	Background = new GameMain_Background;		//
	Score = new GameMain_Score;			//
	ScoreFont = new GameMain_ScoreFont;		//
	Music_Frame = new GameMain_MusicDataFrame;
	Music_FrameBack = new GameMain_MusicFrameBack;
	HoiruButton = new GameMain_HoiruButton;
	Level = new GameMain_Level(reader.GetMusicData()->Jacket.Level);
	LevelFont = new GameMain_LevelFont;
	BPMFont = new GameMain_BPMFont;
	BPM = new GameMain_BPM(reader.GetMusicData()->Jacket.Bpm);
	PushEffect = new GameMain_PushEffect;

	MaxCombo = new GameMain_MaxCombo;
	MaxComboFont = new GameMain_MaxComboFont;
	JacketImage = new GameMain_JacketImage;
	Bar = new GameMain_Bar;
	HiSpeed = new GameMain_HiSpeed;

	//Yuka = new Model_Template;
	Lane = CLane::getInstance();
	NotesMgr = new CNotesMgr(mPlayDataMgr);
	TimeServer = new CTimeServer;
	NotesMgr->SetLaneData(Lane->GetLaneData());
	//NotesMgr->SetDataMgr(mPlayDataMgr);
	Bar->Initialize(Lane->GetLaneData().m_fLaneSize, PushEffect->GetSize().y);

	//NotesMgr->Initialize();
	//thread threadB(bind(&CNotesMgr::SoundPlay, NotesMgr));
	//thread threadA(bind(&CNotesMgr::Initialize, NotesMgr));
	NotesMgr->Initialize();

	//threadB.join();
	//threadA.join();
}

void GameMain_Scene::Finalize()
{

}

//***********************************************************************************************************
// 更新
//***********************************************************************************************************
void GameMain_Scene::Update(void)
{
	CDirectX::Get_pD3DDevice()->ShowCursor(FALSE);
	// ここでオブジェクトのupdate処理
	TimeServer->Update();
	Background->Update();
	Music_Frame->Update();
	Music_FrameBack->Update();
	HoiruButton->Update();
	JacketImage->Update();
	Bar->Update();
	HiSpeed->Update();

	//Yuka->Update();
	Lane->SetSelectLane(Bar->GetSelectLane());
	Lane->Update();

	NotesMgr->SetSelectLane(Bar->GetSelectLane());
	NotesMgr->Update();

	// UI
	Score->SetScore(mPlayDataMgr->GetPlayData(eData_Score));
	Score->Update();
	ScoreFont->Update();
	Level->Update();
	LevelFont->Update();
	BPMFont->Update();
	BPM->Update();
	PushEffect->Update();
	MaxCombo->SetCombo(mPlayDataMgr->GetPlayData(eData_MaxCombo));
	MaxCombo->Update();
	MaxComboFont->Update();

	// 曲再生終了時
	if (NotesMgr->SoundEndCheck())
	{
		mSceneChanger->ChangeScene(eScene_Result);
	}
}

//***********************************************************************************************************
// 描画
//***********************************************************************************************************
void GameMain_Scene::Draw(void)
{
	// 描画順は上の行から順に(但し2Dベース画像はこの限りではありません)
	Background->Draw();			// 背景色

	Music_FrameBack->Draw();	// 曲情報・枠背景色
	Music_Frame->Draw();		// 曲情報・枠
	JacketImage->Draw();		// 曲情報・ジャケット
	Score->Draw();				// スコア数字
	ScoreFont->Draw();			// スコア文字
	MaxCombo->Draw();			// コンボ数字
	MaxComboFont->Draw();		// コンボ文字
	Level->Draw();				// レベル数字
	LevelFont->Draw();			// レベル文字
	BPM->Draw();				// BPM数字
	BPMFont->Draw();			// BPM文字

	HoiruButton->Draw();		// 上下ホイールボタン押す位置
	Bar->Draw();				// 判定バー

	PushEffect->Draw();			// エフェクト
	HiSpeed->Draw();			// 右下ハイスピ

								//Yuka->Draw();				// 床モデル(デバッグ・カメラ確認用)
	Lane->Draw();
	NotesMgr->Draw();
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************