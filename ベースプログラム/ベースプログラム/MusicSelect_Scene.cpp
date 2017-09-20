//***********************************************************************************************************
//
// 曲セレクトシーン一括管理
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS

#include "MusicSelect_Scene.h"
#include "CInput.h"
#include <locale.h>

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
MusicSelect_Scene::MusicSelect_Scene(ISceneChanger* changer, IPlayDataMgr* dataMgr) : CBaseScene(changer)
{
	// ここでオブジェクトのnew処理
	BackGround = new MusicSelect_BackGround;
	BackEffect = new MusicSelect_BackEffect;
	LeftFrame = new MusicSelect_LeftFrame;
	Score = new MusicSelect_Score;
	BPM = new MusicSelect_BPM;
	Illustrator = new MusicSelect_Illustrator;
	Creator = new MusicSelect_Creator;
	RightFrame = new MusicSelect_RightFrame;
	Jacket = new MusicSelect_Jacket;
	Level = new MusicSelect_Level;

	mPlayDataMgr = dataMgr;

	//*******************************************************************************************************
	// 曲総数分サイズ確保
	//*******************************************************************************************************
	M_Data = new MUSICSELECT_ALL_DATA[CMusic_Manager::Get_Music_Count()];
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
MusicSelect_Scene::~MusicSelect_Scene(void)
{
	// ここでオブジェクトのdelete処理
	delete		BackGround;
	delete		BackEffect;
	delete		LeftFrame;
	delete		Score;
	delete		BPM;
	delete		Illustrator;
	delete		Creator;
	delete		RightFrame;
	delete		Jacket;
	delete		Level;

	delete[]	M_Data;
}

void MusicSelect_Scene::Initialize()
{


	//*******************************************************************************************************
	// 曲セレクト画面に必要な情報を全て抽出
	//*******************************************************************************************************
	for (int i = 0; i < CMusic_Manager::Get_Music_Count(); i++)
	{
		// 1回書き込めば良い物の為に使用
		bool bWrite_Flg = false;

		// イージー・ハイパー・マスター譜面読み込み
		for (int j = 0; j < 3; j++)
		{
			// 各難易度で譜面データが無い場合はスキップ
			switch (j)
			{
			case 0:
				if (CMusic_Manager::Get_MusicData(i)->Easy_In == false)
				{
					M_Data[i].Difficult_Level[j] = NULL;
					continue;
				}


				break;
			case 1:
				if (CMusic_Manager::Get_MusicData(i)->Hyper_In == false)
				{
					M_Data[i].Difficult_Level[j] = NULL;
					continue;
				}

				break;

			case 2:
				if (CMusic_Manager::Get_MusicData(i)->Master_In == false)
				{
					M_Data[i].Difficult_Level[j] = NULL;
					continue;
				}

				break;
			}

			// 譜面データ読み込み
			//*************************************************
			string FileName = CMusic_Manager::Get_MusicData(i)->Fumen_Path[j];
			Reader.JacketFileLoad(FileName);

			if (bWrite_Flg == false)
			{
				// 曲名
				//*****************************************************
				M_Data[i].Music_Data.Jacket.TitleName = Reader.GetMusicData()->Jacket.TitleName;

				// BPM
				//*****************************************************
				M_Data[i].Music_Data.Jacket.Bpm = Reader.GetMusicData()->Jacket.Bpm;

				// 作曲者名
				//*****************************************************
				M_Data[i].Music_Data.Jacket.ArtistName = Reader.GetMusicData()->Jacket.ArtistName;

				// ジャケット製作者
				//*****************************************************
				M_Data[i].Music_Data.Jacket.IllustratorName = Reader.GetMusicData()->Jacket.IllustratorName;

				// 譜面製作者
				//*****************************************************
				M_Data[i].Music_Data.Jacket.CreatorName = Reader.GetMusicData()->Jacket.CreatorName;

				// 曲スタート位置
				//*****************************************************
				M_Data[i].Music_Data.Jacket.Pst = Reader.GetMusicData()->Jacket.Pst;

				// 選曲画面で流す音源の長さ
				//*****************************************************
				M_Data[i].Music_Data.Jacket.Ple = Reader.GetMusicData()->Jacket.Ple;

				// 1回書き込んだのでフラグを立てる
				//*****************************************************
				bWrite_Flg = true;
			}

			// 各難易度レベル
			//*********************************************************
			M_Data[i].Difficult_Level[j] = Reader.GetMusicData()->Jacket.Level;

			int Difficult_Work = 0;

			switch (j)
			{
			case   EASY: Difficult_Work = EASY; break;
			case  HYPER: Difficult_Work = HYPER; break;
			case MASTER: Difficult_Work = MASTER; break;
			}

			Level->Set_Level(M_Data[i].Difficult_Level[j], i, Difficult_Work);
		}


	}

	// 現在選択中の曲データを設定
	//*******************************************************************************************************
	nSelect_Data = 3;

	// 現在選択中の難易度をEASYに設定
	//*******************************************************************************************************
	nNow_Difficult = EASY;

	// 上下移動フラグを初期化
	//*******************************************************************************************************
	bMove_Up = false;
	bMove_Down = false;

	// フレームカウントを初期化
	//*******************************************************************************************************
	nFrame_Count = 0;

	// データ変更タイミングを初期化
	//*******************************************************************************************************
	bData_Change_Flg = true;

	// locale.hを使用するため
	//*******************************************************************************************************
	setlocale(LC_ALL, "jpn");
}

void MusicSelect_Scene::Finalize()
{

}

//***********************************************************************************************************
// 更新
//***********************************************************************************************************
void MusicSelect_Scene::Update(void)
{
	
	//*********************************************************************
	// キーボード操作
	//*********************************************************************
	// ↑・↓キーで移動作業、→・左キーで難易度セレクト
	//*********************************************************************
	{
		// ↑キー操作
		if (CInput::GetKeyboardData(DIK_UP, TRIGGER))
		{
			if ( !bMove_Up )
			{
				nSelect_Data ++;
			}

			if ( !bMove_Down )
			{
				bMove_Up = true;
			}
		}

		// ↓キー操作
		if (CInput::GetKeyboardData(DIK_DOWN, TRIGGER))
		{
			if ( !bMove_Down )
			{
				nSelect_Data --;
			}

			if ( !bMove_Up )
			{
				bMove_Down = true;
			}
		}

		// ←キー操作
		if (CInput::GetKeyboardData(DIK_LEFT, TRIGGER))
		{
			switch (nNow_Difficult)
			{
			case EASY:   nNow_Difficult = EASY;  break;
			case HYPER:  nNow_Difficult = EASY;  break;
			case MASTER: nNow_Difficult = HYPER; break;
			}
		}

		// →キー操作
		if (CInput::GetKeyboardData(DIK_RIGHT, TRIGGER))
		{
			switch (nNow_Difficult)
			{
			case EASY:   nNow_Difficult = HYPER;  break;
			case HYPER:  nNow_Difficult = MASTER; break;
			case MASTER: nNow_Difficult = MASTER; break;
			}
		}
	}

	// エンターキーで選択中の曲情報を渡して、ゲームメインへ移動
	if (CInput::GetKeyboardData(DIK_RETURN, TRIGGER))
	{
		// 選択された曲情報を渡す
		mPlayDataMgr->SetPlayData(eData_SelectMusicNum, nSelect_Data);
		mPlayDataMgr->SetPlayData(eData_Difficult, nNow_Difficult);

		// ゲームシーンへ移行
		mSceneChanger->ChangeScene(eScene_Game);
	}

	if (bMove_Up == true || bMove_Down == true)
	{
		nFrame_Count++;

		if ( nFrame_Count >= 10 + 1 )
		{
			nFrame_Count	 = 0;
			bMove_Up		 = false;
			bMove_Down		 = false;
			bData_Change_Flg = true;
		}
	}
		

	if (nSelect_Data < 0)
	{	// 選曲データ番地がマイナス値に行ったら最大値-1 に修正
		nSelect_Data = CMusic_Manager::Get_Music_Count() - 1;
	}

	if (nSelect_Data >= CMusic_Manager::Get_Music_Count())
	{	// 選曲データ番地が最大値に行ったら0 に修正
		nSelect_Data = 0;
	}

	// ここでオブジェクトのupdate処理
	BackGround->Update();								// 背景
	BackEffect->Update();								// 背景エフェクト
	LeftFrame->Update();								// 左情報枠
	BPM->Update(M_Data[nSelect_Data].Music_Data.Jacket.Bpm);	// BPM

	//*********************************************************************
	// string を wchar_tに変換
	//*********************************************************************
	wchar_t	wStrW[100];
	int		Len = 0;

	// ジャケット製作者名変換
	//**********************************
	{	
		// string → char* に変換
		//**************************************************
		char* sz_Illustrator = new char[M_Data[nSelect_Data].Music_Data.Jacket.IllustratorName.size() + 1];
		std::strcpy(sz_Illustrator, M_Data[nSelect_Data].Music_Data.Jacket.IllustratorName.c_str());
		// char* → wchar_t に変換
		//**************************************************
		Len = mbstowcs(wStrW, sz_Illustrator, 100);

		delete[] sz_Illustrator;
	}

	// ジャケット製作者
	Illustrator->Update( wStrW, Len, bData_Change_Flg );		

	// 譜面製作者名変換
	//**********************************
	{	
		// string → char* に変換
		//**************************************************
		char* sz_CreatorName = new char[M_Data[nSelect_Data].Music_Data.Jacket.CreatorName.size() + 1];
		std::strcpy(sz_CreatorName, M_Data[nSelect_Data].Music_Data.Jacket.CreatorName.c_str());
		// char* → wchar_t に変換
		//**************************************************
		Len = mbstowcs(wStrW, sz_CreatorName, 100);

		delete[] sz_CreatorName;
	}

	// 譜面製作者
	Creator->Update( wStrW, Len, bData_Change_Flg );			

	int nDisp_Score = 0;

	switch ( nNow_Difficult )
	{
	case   EASY: nDisp_Score = CMusic_Manager::Get_MusicData(nSelect_Data)->Easy_Hiscore;   break;
	case  HYPER: nDisp_Score = CMusic_Manager::Get_MusicData(nSelect_Data)->Hyper_Hiscore;  break;
	case MASTER: nDisp_Score = CMusic_Manager::Get_MusicData(nSelect_Data)->Master_Hiscore; break;
	}

	RightFrame->Update( nNow_Difficult, bMove_Up, bMove_Down );
	Jacket->Update( bMove_Up, bMove_Down );
	Level->Update( bMove_Up, bMove_Down );

	Score->Update( nDisp_Score );			// ハイスコア

	bData_Change_Flg = false;
}

//***********************************************************************************************************
// 描画
//***********************************************************************************************************
void MusicSelect_Scene::Draw(void)
{
	// 描画順は上の行から順に(但し2Dベース画像はこの限りではありません)
	BackGround->Draw();
	BackEffect->Draw();
	LeftFrame->Draw();
	BPM->Draw();
	Illustrator->Draw();
	Creator->Draw();

	// 右情報まとめ
	for ( int i = 0 ; i < 7 ; i ++ )
	{
		// フレーム描画
		int nJacketWork = RightFrame->Draw(i);


		// ジャケット描画
		Jacket->Draw(nJacketWork);

		// 各難易度レベル描画
		Level->Draw(nJacketWork);
	}

	Score->Draw();
}