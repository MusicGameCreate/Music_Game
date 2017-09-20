//***********************************************************************************************************
//　CScene_Base.cpp
//	シーン切り替えクラス
//***********************************************************************************************************
#include "SceneMgr.h"
#include "Title_Scene.h"		// タイトル画面
#include "ModeSelect_Scene.h"	// モードセレクト画面
#include "Option_Scene.h"		// オプション画面
#include "MusicSelect_Scene.h"	// 曲セレクト画面
#include "GameMain_Scene.h"		// ゲームメイン画面
#include "Result_Scene.h"		// リザルト画面

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
CSceneMgr::CSceneMgr()
{
	mScene = (CBaseScene*)new MusicSelect_Scene(this, this);
	mScene->Initialize();
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
CSceneMgr::~CSceneMgr()
{

}

//***********************************************************************************************************
// void CScene_Base::Init
// 説明：初期化処理
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void CSceneMgr::Initialize()
{
}

void CSceneMgr::Finalize()
{
	mScene->Finalize();
}

//***********************************************************************************************************
// void CScene_Base::Update
// 説明：現在シーンを検査 更新、描画、終了処理へ
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void CSceneMgr::Update()
{
	while (1)
	{
		if (mNextScene != eScene_None && mNextScene != eScene_End)
		{// 次のシーンがセットされていれば
			mScene->Finalize();	// 現在のシーンの終了処理を実行
			delete mScene;
			switch (mNextScene)
			{
			case eScene_Title:
				mScene = (CBaseScene*) new Title_Scene(this);	// タイトル画面のインスタンスを作成
				break;
			case eScene_ModeSelect:
				mScene = (CBaseScene*) new ModeSelect_Scene(this);
				break;
			case eScene_Option:
				mScene = (CBaseScene*) new Option_Scene(this);
				break;
			case eScene_MusicSelect:
				mScene = (CBaseScene*) new MusicSelect_Scene(this, this);
				break;
			case eScene_Game:
				mScene = (CBaseScene*) new GameMain_Scene(this, this);
				break;
			case eScene_Result:
				mScene = (CBaseScene*) new Result_Scene(this, this);
				break;
			};
			mNextScene = eScene_None;
			mScene->Initialize();
		}
		mScene->Update(); //次のシーンの更新
		if (mNextScene == eScene_None || mNextScene == eScene_End)
			break;
	}
}

// 描画処理
void CSceneMgr::Draw(void)
{
	mScene->Draw();
}

// 次のシーンを設定
void CSceneMgr::ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;	// 次のシーンをセット
}

void CSceneMgr::SetPlayData(eDataType datatype, int nData)
{
	mPlayDataMgr.SetPlayData(datatype, nData);
}

int CSceneMgr::GetPlayData(eDataType datatype)
{
	return mPlayDataMgr.GetPlayData(datatype);
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************