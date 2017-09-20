//***********************************************************************************************************
//
// 全シーン一括管理
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
//#include "Title_Scene.h"		// タイトル画面
//#include "ModeSelect_Scene.h"	// モードセレクト画面
//#include "Option_Scene.h"		// オプション画面
//#include "MusicSelect_Scene.h"	// 曲セレクト画面
//#include "GameMain_Scene.h"		// ゲームメイン画面
//#include "Result_Scene.h"		// リザルト画面
//#include "Fade_Scene.h"			// フェード画面
//#include "Load_Scene.h"			// ロード画面
#include "BaseScene.h"
#include "PlayDataMgr.h"

//#include "CTimer.h"
//#include "CInput.h"

//***********************************************************************************************************
// クラス定義
//***********************************************************************************************************
class CSceneMgr : public ISceneChanger, IPlayDataMgr
{
private:
	//Title_Scene*		Title_;			// タイトルシーン一括管理
	//ModeSelect_Scene*	ModeSelect_;	// モードセレクトシーン一括管理
	//Option_Scene*		Option_;		// オプションシーン一括管理
	//MusicSelect_Scene*	MusicSelect_;	// 曲セレクトシーン一括管理
	//GameMain_Scene*		GameMain_;		// ゲームメインシーン一括管理
	//Result_Scene*		Result_;		// リザルトシーン一括管理
	//Fade_Scene*			Fade_;			// フェードシーン一括管理
	//Load_Scene*			Load_;			// ロードシーン一括管理
	
	//double				Timer;

	CBaseScene*			mScene;			// 現在のシーン
	eScene				mNextScene;		// 変更後のシーン
	PlayDataMgr			mPlayDataMgr;	// データ管理
public:

	CSceneMgr(void);
	~CSceneMgr(void) override;
	void Initialize(void);
	void Finalize(void);
	void Update(void);
	void Draw(void);

	void SetPlayData(eDataType datatype, int nData)override;
	int GetPlayData(eDataType datatype) override;
	void ChangeScene(eScene NextScene) override;
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************