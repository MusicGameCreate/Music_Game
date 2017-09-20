#include "NotesMgr.h"
#include "TimeServer.h"
#include "CMusic_Manager.h"

//#include <boost/bind.hpp>
//#include <boost/thread.hpp>

//using namespace boost;

const int InitEmptyLane = 2;	// 最初に流す空レーンの長さ

// コンストラクタ
CNotesMgr::CNotesMgr(IPlayDataMgr* dataMgr)
{
	SoundTimer = 0.0f;
	EmptyTime = 0.0f;
	Score = 0;
	InitFlag = false;
	EmptyFlag = true;
	CreateFlag = false;
	InitSoundFlag = false;
	InitSoundCounter = 0;
	InitSoundCounterBase = 0.0f;
	CourceTime = 0.0f;
	//sound.Init("../DATA/BGM/Main.wav");
	//sound.SetCurrentPosition(10);
	//sound.Play(true);
	InitCount = 0;
	//bar.Init();
	PlayingTime = 0;
	start = 0;
	Playing = false;
	SelectLane.clear();

	PerfectCount = 0;
	GreatQuickCount = 0;
	GreatSlowCount = 0;
	GoodQuickCount = 0;
	GoodSlowCount = 0;
	MissCount = 0;

	OverTime = 0.0f;

	mPlayDataMgr = dataMgr;
	MusicNum = mPlayDataMgr->GetPlayData(eData_SelectMusicNum);
}

// デストラクタ
CNotesMgr::~CNotesMgr()
{
	//Finalize();
}

// 初期化関数
void CNotesMgr::Initialize()
{
	CNotesMgr::Load();
}

// データ読み込み関数
void CNotesMgr::Load()
{
	// サウンド読み込み
	GameMusic = new CSound;
	GameMusic->Init(CMusic_Manager::Get_MusicData(MusicNum)->Music_Path);
	//GameMusic->Init("../DATA/MUSIC/badapple.music/badapple.wav");
	//GameMusic->Init("../DATA/MUSIC/LemonadeParty.music/LemonadeParty.wav");// ここで渡された曲のパスにアクセス
	//Playing = GameMusic->GetPlaying();
	//start = GameMusic->GetStatus();
	//start = (double)clock() / CLOCKS_PER_SEC;
	//Playing = GameMusic->GetPlaying();

	// 変数初期化
	for (int i = 0; i < 6; i++)
	{
		NotesNum[i] = 0;
	}
	//nCount = 0;
	BeatCount = 0;

	// 譜面読み込み
	reader.MusicDataLoad(CMusic_Manager::Get_MusicData(MusicNum)->Fumen_Path[mPlayDataMgr->GetPlayData(eData_Difficult)]);
	//reader.FileRead("../DATA/TEXT/sample.score");
	//reader.FileRead("../DATA/MUSIC/LemonadeParty.music/lemon_E.score");// ここで渡された譜面のパスにアクセス
	//reader.FileRead("../DATA/MUSIC/LemonadeParty.music/lemon.score");// ここで渡された譜面のパスにアクセス


	//GameMusic->Play(false);
	//GameMusic->Change_Volume(-10000);
	//GameMusic->SetCurrentPosition(GameMusic->GetSoundFileLength());

	// ハイスピ処理
	Bpm = reader.GetMusicData()->Jacket.Bpm;			// BPM格納
	HiSpeed = 1.0f;								// プレイヤーが設定したハイスピを代入

	MajorBeatTime = 60.0f / (double)Bpm / 4.0f;	// 16分の時間
	MajorTime = MajorBeatTime * 16.0f;			// 一小節の時間

	NotesNum[NOTES_LIST_NORMAL_L] = reader.GetMusicData()->Notes.NotesCount.Normal_L_Count;
	NotesNum[NOTES_LIST_NORMAL_L_LONG] = reader.GetMusicData()->Notes.NotesCount.Normal_L_Long_Count;
	NotesNum[NOTES_LIST_NORMAL_R] = reader.GetMusicData()->Notes.NotesCount.Normal_R_Count;
	NotesNum[NOTES_LIST_NORMAL_R_LONG] = reader.GetMusicData()->Notes.NotesCount.Normal_R_Long_Count;
	NotesNum[NOTES_LIST_CLICK_L] = reader.GetMusicData()->Notes.NotesCount.Click_L_Count;
	NotesNum[NOTES_LIST_CLICK_L_LONG] = reader.GetMusicData()->Notes.NotesCount.Click_L_Long_Count;
	NotesNum[NOTES_LIST_CLICK_R] = reader.GetMusicData()->Notes.NotesCount.Click_R_Count;
	NotesNum[NOTES_LIST_CLICK_R_LONG] = reader.GetMusicData()->Notes.NotesCount.Click_R_Long_Count;
	NotesNum[NOTES_LIST_WHEEL_U] = reader.GetMusicData()->Notes.NotesCount.Wheel_U_Count;
	NotesNum[NOTES_LIST_WHEEL_D] = reader.GetMusicData()->Notes.NotesCount.Wheel_D_Count;

	//CBaseNotes normal_L;

	//normal_L.Initialize("../DATA/TEXTURE/GameMain/Notes/黄ノーツ.png", Data);

	//NormalLeftNotes		= new vector<CBaseNotes>[NotesNum[NOTES_LIST_NORMAL_L]];
	//NormalLeftLongNotes = new CLongNotes[NotesNum[NOTES_LIST_NORMAL_L_LONG]];
	//NormalRightNotes		= new CBaseNotes[NotesNum[NOTES_LIST_NORMAL_R]];
	//NormalRightLongNotes = new CLongNotes[NotesNum[NOTES_LIST_NORMAL_R_LONG]];
	//ClickLeftNotes		= new CBaseNotes[NotesNum[NOTES_LIST_CLICK_L]];
	//ClickLeftLongNotes	= new CLongNotes[NotesNum[NOTES_LIST_CLICK_L_LONG]];
	//ClickRightNotes		= new CBaseNotes[NotesNum[NOTES_LIST_CLICK_R]];
	//ClickRightLongNotes	= new CLongNotes[NotesNum[NOTES_LIST_CLICK_R_LONG]];
	//WheelUpNotes		= new CWheelNotes[NotesNum[NOTES_LIST_WHEEL_U]];
	//WheelDownNotes		= new CWheelNotes[NotesNum[NOTES_LIST_WHEEL_D]];

	int i = 0;
	// 左ノーマル
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L]; i++)
	{
		NormalLeftNotes.push_back(new CBaseNotes());
		NormalLeftNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/黄ノーツ.png", Data);
	}

	// 左ノーマルロング
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L_LONG]; i++)
	{
		NormalLeftLongNotes.push_back(new CLongNotes());
		NormalLeftLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/ロング間黄.png", Data);
	}

	// 右ノーマル
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R]; i++)
	{
		NormalRightNotes.push_back(new CBaseNotes());
		NormalRightNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/黄ノーツ.png", Data);
	}

	// 右ノーマルロング
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R_LONG]; i++)
	{
		NormalRightLongNotes.push_back(new CLongNotes());
		NormalRightLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/ロング間黄.png", Data);
	}

	// 左クリック
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L]; i++)
	{
		ClickLeftNotes.push_back(new CBaseNotes());
		ClickLeftNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/黄緑ノーツ.png", Data);
	}

	// 左クリックロング
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L_LONG]; i++)
	{
		ClickLeftLongNotes.push_back(new CLongNotes());
		ClickLeftLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/ロング間黄緑.png", Data);
	}

	// 右クリック
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R]; i++)
	{
		ClickRightNotes.push_back(new CBaseNotes());
		ClickRightNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/黄緑ノーツ.png", Data);
	}

	// 右クリックロング
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R_LONG]; i++)
	{
		ClickRightLongNotes.push_back(new CLongNotes());
		ClickRightLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/ロング間黄緑.png", Data);
	}

	// 上ホイール
	for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_U]; i++)
	{
		WheelUpNotes.push_back(new CWheelNotes());
		WheelUpNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/上方向青.png", Data);
	}

	// 下ホイール
	for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_D]; i++)
	{
		WheelDownNotes.push_back(new CWheelNotes());
		WheelDownNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/下方向青.png", Data);
	}

	AllSetSpeed(Bpm, HiSpeed);

	for (i = 0; i < LANE_NUM * 2; i++)
	{
		m_NotesEffect.push_back(new CNotesEffect());
		m_NotesEffect[i]->Initialize(Data);
	}

	//for(int loop = 0; loop < 15; loop ++)
	//{
	//	debug.Init("../DATA/BGM/Main.wav");
	//}

	InitFlag = true;

	SoundEndFlag = false;
	OldSound = 0;

	GameMusic->Play(false);
}

// 終了関数
void CNotesMgr::Finalize()
{
	// 左ノーマル
	for (vector<CBaseNotes*>::iterator it = NormalLeftNotes.begin(); it != NormalLeftNotes.end(); it++)
	{
		delete (*it);
	}

	// 左ノーマルロング
	for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
	{
		delete (*it);
	}

	// 右ノーマル
	for (vector<CBaseNotes*>::iterator it = NormalRightNotes.begin(); it != NormalRightNotes.end(); it++)
	{
		delete (*it);
	}

	// 右ノーマルロング
	for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
	{
		delete (*it);
	}

	// 左クリック
	for (vector<CBaseNotes*>::iterator it = ClickLeftNotes.begin(); it != ClickLeftNotes.end(); it++)
	{
		delete (*it);
	}

	// 左クリックロング
	for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
	{
		delete (*it);
	}

	// 右クリック
	for (vector<CBaseNotes*>::iterator it = ClickRightNotes.begin(); it != ClickRightNotes.end(); it++)
	{
		delete (*it);
	}

	// 右クリックロング
	for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
	{
		delete (*it);
	}

	// 上ホイール
	for (vector<CWheelNotes*>::iterator it = WheelUpNotes.begin(); it != WheelUpNotes.end(); it++)
	{
		delete (*it);
	}

	// 下ホイール
	for (vector<CWheelNotes*>::iterator it = WheelDownNotes.begin(); it != WheelDownNotes.end(); it++)
	{
		delete (*it);
	}

	NormalLeftNotes.clear();
	NormalLeftLongNotes.clear();
	NormalRightNotes.clear();
	NormalRightLongNotes.clear();
	ClickLeftNotes.clear();
	ClickLeftLongNotes.clear();
	ClickRightNotes.clear();
	ClickRightLongNotes.clear();
	WheelUpNotes.clear();
	WheelDownNotes.clear();

	for (int i = 0; i < Data.m_nLaneNum * 2; i++)
	{
		m_NotesEffect.push_back(new CNotesEffect());
	}
	m_NotesEffect.clear();

	GameMusic->Stop();
	delete		GameMusic;
}

// 更新関数
void CNotesMgr::Update()
{
	// 曲が再生中になるまで待機
	if (!Playing)
	{
		DWORD status;
		status = GameMusic->GetStatus();
		//PlayingTime = clock() / CLOCKS_PER_SEC;
		//Last = PlayingTime - start;
		if (status == 17/* && InitCount == 0*/)
		{// 再生状態
		 // 事前にノーツを配置する
			int Cnt = 0;
			double BpmSize = ((Bpm * HiSpeed) * BPM_SPEED);				// 1秒間で進む距離
			double MajorSize = BpmSize * (MajorTime * InitEmptyLane);	// 2小節の時間で進む距離
			double MajorBeatSize = (BpmSize * MajorBeatTime);				// 16分の時間で進む距離
			double LifeTime = (Data.m_vTexSize.x * HiSpeed) / BpmSize;	// レーンの端から端までにかかる時間

																		// 2小節で進む距離がレーンの長さより短い場合は画面に映る分のノーツを先に配置する。
			if (Data.m_vTexSize.x >= MajorSize)
			{
				EmptyFlag = false;
				// 配置位置がレーンの長さを超えるまで配置し続ける
				for (Cnt = 0; Data.m_vTexSize.x >= MajorSize + (MajorBeatSize * Cnt); Cnt++)
				{
					// 通常の生成位置からどれだけ離れているか計算して引数に渡す
					CourceTime = (((Data.m_vTexSize.x * HiSpeed) - MajorSize) - (MajorBeatSize * Cnt)) / (Data.m_vTexSize.x * HiSpeed);
					NotesCreate(LifeTime * CourceTime);
					//NotesCreate(((Data.m_vTexSize.x - MajorSize) / Data.m_vTexSize.x) )
				}
				// 配置し終えた後に隙間があるなら初期からある超過時間として保存
				//CourceTime = ((Data.m_vTexSize.x - MajorSize) - (BpmSize * (MajorBeatTime * Cnt))) / Data.m_vTexSize.x;
			}
			else
			{// 2小節の時間で進む距離がレーンの長さより長い場合は、残り何秒待てば2小節の時間になるか計算する
				double MoveSize = (Data.m_vTexSize.x / BpmSize);
				EmptyFlag = true;
				EmptyTime = MoveSize;
				OverTime = MoveSize;
			}

			GameMusic->Stop();
			GameMusic->SetCurrentPosition(0);
			//GameMusic->StartSet();
			//InitCount++;
			Playing = true;
		}
		//if (InitCount < 10)
		//	InitCount++;
		//else
		//{
		//	Playing = true;
		//}
		return;
	}

	double addTime = CTimeServer::GetDifference();
	double NowSound = GameMusic->GetNowPlayTime();

	if (!EmptyFlag)
	{
		if (!InitSoundFlag)
		{
			EmptyTime += addTime;// 前フレームからの経過時間を加算
			InitSoundCounterBase += addTime;
			if (EmptyTime + CourceTime >= MajorBeatTime)// 16分の生成時間
			{
				EmptyTime -= MajorBeatTime;
				NotesCreate(EmptyTime);
				InitSoundCounter++;
			}

			// 音が遅延するよおおおおおおおおおおおおお
			if (OverTime)
			{
				if (InitSoundCounterBase + ((MajorTime * InitEmptyLane) - OverTime) >= (MajorTime * InitEmptyLane) - (0.6f))// なんとか合わせろ
				{
					//SoundTimer = -EmptyTime;
					GameMusic->Play(false);
					//InitSoundFlag = true;
					SoundTimer = -EmptyTime;
					InitSoundFlag = true;
				}
			}
			else
			{
				if (InitSoundCounterBase >= (MajorTime * InitEmptyLane) - (0.6f))// なんとか合わせろ
				{
					//SoundTimer = -EmptyTime;
					GameMusic->Play(false);
					//InitSoundFlag = true;
					SoundTimer = -EmptyTime;
					InitSoundFlag = true;
				}
			}

			//if (InitSoundCounter >= 11)
			//{
			//	SoundTimer = -EmptyTime; 
			//	InitSoundFlag = true;
			//}
		}

		// ノーツ生成
		if (!CreateFlag && (NowSound - SoundTimer) * HiSpeed >= MajorBeatTime)
		{
			CreateFlag = true;
			//SoundTimer = NotesTimer = NowSound;

			//if (!InitSoundFlag && (NotesTimer - MajorTime * (InitEmptyLane - 1)) > MajorTime)
			//{
			//	InitSoundFlag = true;
			//}
			if (BeatCount != reader.GetMusicData()->Notes.NotesCount.MajorCount)
			{
				NotesCreate(((NowSound - SoundTimer) * HiSpeed) - MajorBeatTime);

				//if (BeatCount + 1 < reader.GetMusicData()->Notes.NotesCount.MajorCount)
				//BeatCount++;
			}
		}

		// 次のノーツを生成出来るようにする
		if (NowSound - SoundTimer >= MajorBeatTime)
		{
			SoundTimer += MajorBeatTime;
			CreateFlag = false;
		}

		if (OldSound > NowSound && !SoundEndFlag)
		{
			SoundEndFlag = true;
		}
	}
	else
	{// EmptyFlag == trueの場合ノーツ生成が始まるまで空レーン再生
		EmptyTime += addTime;

		//// ノーツ生成
		//if (EmptyTime + CourceTime >= MajorBeatTime)
		//{
		//	NotesCreate(((NowSound - SoundTimer) * HiSpeed) - MajorBeatTime);
		//}

		// 2小節分の長さがレーンの端まで来たらノーツ再生を行う。
		if (EmptyTime >= (MajorTime * (InitEmptyLane)))
		{
			EmptyFlag = false;
			EmptyTime -= (MajorTime * (InitEmptyLane))/* - (MajorBeatTime * 2)*/;
			NotesCreate(EmptyTime);
		}

		//EmptyTime += addTime;
	}

	OldSound = NowSound;

	//// ノーツ更新
	//for (int i = 0; i < NOTES_LIST_MAX; i++)
	//{
	//	for (int j = 0; j < NotesNum[i]; j++)
	//	{
	//		if (!NotesList[i][j]->GetUseFlag())
	//			continue;
	//		NotesList[i][j]->Update();
	//		if (!NotesList[i][j]->GetUseFlag())
	//			NowCombo = 0;
	//	}
	//}

	// ---ノーツ更新---
	// 左ノーマル
	for (vector<CBaseNotes*>::iterator it = NormalLeftNotes.begin(); it != NormalLeftNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if (!(*it)->GetUseFlag())
		{
			MissCount++;
			NowCombo = 0;
		}
	}

	// 左ノーマルロング
	for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if ((*it)->GetMissFlag())
		{
			(*it)->SetMissFlag(false);
			MissCount++;
			NowCombo = 0;
		}
	}

	// 右ノーマル
	for (vector<CBaseNotes*>::iterator it = NormalRightNotes.begin(); it != NormalRightNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if (!(*it)->GetUseFlag())
		{
			MissCount++;
			NowCombo = 0;
		}
	}

	// 右ノーマルロング
	for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if ((*it)->GetMissFlag())
		{
			(*it)->SetMissFlag(false);
			MissCount++;
			NowCombo = 0;
		}
	}

	// 左クリック
	for (vector<CBaseNotes*>::iterator it = ClickLeftNotes.begin(); it != ClickLeftNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if (!(*it)->GetUseFlag())
		{
			MissCount++;
			NowCombo = 0;
		}
	}

	// 左クリックロング
	for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if ((*it)->GetMissFlag())
		{
			(*it)->SetMissFlag(false);
			MissCount++;
			NowCombo = 0;
		}
	}

	// 右クリック
	for (vector<CBaseNotes*>::iterator it = ClickRightNotes.begin(); it != ClickRightNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if (!(*it)->GetUseFlag())
		{
			MissCount++;
			NowCombo = 0;
		}
	}

	// 右クリックロング
	for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if ((*it)->GetMissFlag())
		{
			(*it)->SetMissFlag(false);
			MissCount++;
			NowCombo = 0;
		}
	}

	// 上ホイール
	for (vector<CWheelNotes*>::iterator it = WheelUpNotes.begin(); it != WheelUpNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if (!(*it)->GetUseFlag())
		{
			MissCount++;
			NowCombo = 0;
		}
	}

	// 下ホイール
	for (vector<CWheelNotes*>::iterator it = WheelDownNotes.begin(); it != WheelDownNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
		if (!(*it)->GetUseFlag())
		{
			MissCount++;
			NowCombo = 0;
		}
	}

	// ノーツエフェクト
	for (vector<CNotesEffect*>::iterator it = m_NotesEffect.begin(); it != m_NotesEffect.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
	}

	NotesDecision.Update();

	// ノーツ判定
	NotesDecition();

	mPlayDataMgr->SetPlayData(eData_MaxCombo, NowCombo);
}

// 描画関数
void CNotesMgr::Draw()
{
	//for (int i = 0; i < NOTES_LIST_MAX; i++)
	//{
	//	for (int j = 0; j < NotesNum[i]; j++)
	//	{
	//		if (!NotesList[i][j]->GetUseFlag())
	//			continue;
	//		NotesList[i][j]->Draw();
	//	}
	//}


	// 左ノーマル
	for (vector<CBaseNotes*>::iterator it = NormalLeftNotes.begin(); it != NormalLeftNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 左ノーマルロング
	for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 右ノーマル
	for (vector<CBaseNotes*>::iterator it = NormalRightNotes.begin(); it != NormalRightNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 右ノーマルロング
	for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 左クリック
	for (vector<CBaseNotes*>::iterator it = ClickLeftNotes.begin(); it != ClickLeftNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 左クリックロング
	for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 右クリック
	for (vector<CBaseNotes*>::iterator it = ClickRightNotes.begin(); it != ClickRightNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 右クリックロング
	for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 上ホイール
	for (vector<CWheelNotes*>::iterator it = WheelUpNotes.begin(); it != WheelUpNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// 下ホイール
	for (vector<CWheelNotes*>::iterator it = WheelDownNotes.begin(); it != WheelDownNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// ノーツエフェクト
	for (vector<CNotesEffect*>::iterator it = m_NotesEffect.begin(); it != m_NotesEffect.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	NotesDecision.Draw();
}

// 速度設定関数
void CNotesMgr::AllSetSpeed(double bpm, double hispeed)
{
	int i = 0;
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L]; i++)
	{
		NormalLeftNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L_LONG]; i++)
	{
		NormalLeftLongNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R]; i++)
	{
		NormalRightNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R_LONG]; i++)
	{
		NormalRightLongNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L]; i++)
	{
		ClickLeftNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L_LONG]; i++)
	{
		ClickLeftLongNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R]; i++)
	{
		ClickRightNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R_LONG]; i++)
	{
		ClickRightLongNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_U]; i++)
	{
		WheelUpNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}

	for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_D]; i++)
	{
		WheelDownNotes[i]->SetSpeed(bpm, hispeed, MajorTime);
	}
}

// ノーツ生成関数
void CNotesMgr::NotesCreate(double EmptyTime)
{
	int i = 0;
	int num = 0;
	if (BeatCount + 1 > reader.GetMusicData()->Notes.NotesCount.MajorCount)
		return;
	deque<int> Normal_L = reader.GetNotesData(NOTES_LIST_NORMAL_L);
	deque<int> Normal_L_Long = reader.GetNotesData(NOTES_LIST_NORMAL_L_LONG);
	deque<int> Normal_R = reader.GetNotesData(NOTES_LIST_NORMAL_R);
	deque<int> Normal_R_Long = reader.GetNotesData(NOTES_LIST_NORMAL_R_LONG);
	deque<int> Click_L = reader.GetNotesData(NOTES_LIST_CLICK_L);
	deque<int> Click_L_Long = reader.GetNotesData(NOTES_LIST_CLICK_L_LONG);
	deque<int> Click_R = reader.GetNotesData(NOTES_LIST_CLICK_R);
	deque<int> Click_R_Long = reader.GetNotesData(NOTES_LIST_CLICK_R_LONG);
	deque<int> Wheel_U = reader.GetNotesData(NOTES_LIST_WHEEL_U);
	deque<int> Wheel_D = reader.GetNotesData(NOTES_LIST_WHEEL_D);

	BeatCount++;

	// 左ノーマルノーツ
	for (deque<int>::iterator it = Normal_L.begin(); it != Normal_L.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// ノーマルノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_NORMAL_L]; num++)
			{
				if (NormalLeftNotes[num]->GetUseFlag())
					continue;
				NormalLeftNotes[num]->Create(LANE_LEFT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 左ロングノーマルノーツ
	for (deque<int>::iterator it = Normal_L_Long.begin(); it != Normal_L_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// ロングノーツ
			for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
			{
				if ((*it)->GetUseFlag())
					continue;
				(*it)->SetNotesSize(reader.GetLongNum(NOTES_LIST_NORMAL_L_LONG));
				(*it)->Create(LANE_LEFT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 右ノーマルノーツ
	for (deque<int>::iterator it = Normal_R.begin(); it != Normal_R.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// ノーマルノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_NORMAL_R]; num++)
			{
				if (NormalRightNotes[num]->GetUseFlag())
					continue;
				NormalRightNotes[num]->Create(LANE_RIGHT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 右ノーマルロングノーツ
	for (deque<int>::iterator it = Normal_R_Long.begin(); it != Normal_R_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// ロングノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_NORMAL_R_LONG]; num++)
			{
				if (NormalRightLongNotes[num]->GetUseFlag())
					continue;
				NormalRightLongNotes[num]->SetNotesSize(reader.GetLongNum(NOTES_LIST_NORMAL_R_LONG));
				NormalRightLongNotes[num]->Create(LANE_RIGHT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 左クリックノーツ
	for (deque<int>::iterator it = Click_L.begin(); it != Click_L.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// ノーマルノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_CLICK_L]; num++)
			{
				if (ClickLeftNotes[num]->GetUseFlag())
					continue;
				ClickLeftNotes[num]->Create(LANE_LEFT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 左クリックロングノーツ
	for (deque<int>::iterator it = Click_L_Long.begin(); it != Click_L_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// ロングノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_CLICK_L_LONG]; num++)
			{
				if (ClickLeftLongNotes[num]->GetUseFlag())
					continue;
				ClickLeftLongNotes[num]->SetNotesSize(reader.GetLongNum(NOTES_LIST_CLICK_L_LONG));
				ClickLeftLongNotes[num]->Create(LANE_LEFT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 右クリックノーツ
	for (deque<int>::iterator it = Click_R.begin(); it != Click_R.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// ノーマルノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_CLICK_R]; num++)
			{
				if (ClickRightNotes[num]->GetUseFlag())
					continue;
				ClickRightNotes[num]->Create(LANE_RIGHT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 右クリックロングノーツ
	for (deque<int>::iterator it = Click_R_Long.begin(); it != Click_R_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// ロングノーツ
			for (num = 0; num < NotesNum[NOTES_LIST_CLICK_R_LONG]; num++)
			{
				if (ClickRightLongNotes[num]->GetUseFlag())
					continue;
				ClickRightLongNotes[num]->SetNotesSize(reader.GetLongNum(NOTES_LIST_CLICK_R_LONG));
				ClickRightLongNotes[num]->Create(LANE_RIGHT, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 上ホイールノーツ
	for (deque<int>::iterator it = Wheel_U.begin(); it != Wheel_U.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// 上レーン
			for (num = 0; num < NotesNum[NOTES_LIST_WHEEL_U]; num++)
			{
				if (WheelUpNotes[num]->GetUseFlag())
					continue;
				WheelUpNotes[num]->Create(type - 1, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
	i = 0;
	// 下ホイールノーツ
	for (deque<int>::iterator it = Wheel_D.begin(); it != Wheel_D.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// 下レーン
			for (num = 0; num < NotesNum[NOTES_LIST_WHEEL_D]; num++)
			{
				if (WheelDownNotes[num]->GetUseFlag())
					continue;
				WheelDownNotes[num]->Create(type - 1, i, EmptyTime + CourceTime);
				break;
			}
			break;
		default:
			break;
		}
	}
}

// ノーツ判定関数
void CNotesMgr::NotesDecition()
{
	double timing = 0.0f;
	int i = 0, j = 0;
	int Up = SelectLane.front();
	int Down = SelectLane.back();
	// ---ノーツ判定---
	// 左ノーマルノーツ
	if (CInput::GetKeyboardData(DIK_Z, TRIGGER) || CInput::GetKeyboardData(DIK_X, TRIGGER))
	{
		timing = HIT_TIMING;
		int Quick = -1;// 一番速いノーツの番号
		for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L]; i++)
		{
			// ノーツが生きているか
			if (!NormalLeftNotes[i]->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				// 一致していれば抜ける
				if (NormalLeftNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			// 一致せず抜けていれば戻る
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if (fabs(NormalLeftNotes[i]->GetTiming()) < HIT_TIMING)
			{
				// 判定に入っているものの中で一番近ければ値更新
				if (fabs(NormalLeftNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = NormalLeftNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// ノーツエフェクト
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(NormalLeftNotes[Quick]->GetLaneNum());
				break;
			}
			// ノーツを消す処理やスコア加算やなんやかんや
			NormalScoreAdd(timing);
			NormalLeftNotes[Quick]->SetUseFlag(false);
			ComboAdd();
			CLane::getInstance()->NotesEffect(NormalLeftNotes[Quick]->GetLaneNum(), NormalLeftNotes[Quick]->GetLaneType());
		}
	}
	// 左ノーマルロングノーツ
	if (CInput::GetKeyboardData(DIK_Z, PRESS) || CInput::GetKeyboardData(DIK_X, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
		{
			// ノーツが生きているか
			if (!(*it)->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				// 一致していれば抜ける
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// 一致せず抜けていれば戻る
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// スコア加算やなんやかんや
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// ノーツエフェクト
					for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
					{
						if ((*it2)->GetUseFlag())
							continue;
						(*it2)->Create((*it)->GetLaneNum());
					}
				}
				else
				{
					CLane::getInstance()->TimerReset((*it)->GetLaneNum(), (*it)->GetLaneType());
				}
			}
		}
	}

	// 右ノーマルノーツ
	if (CInput::GetKeyboardData(DIK_C, TRIGGER) || CInput::GetKeyboardData(DIK_V, TRIGGER))
	{
		int Quick = -1;// 一番速いノーツの番号
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R]; i++)
		{
			// ノーツが生きているか
			if (!NormalRightNotes[i]->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				if (NormalRightNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if (fabs(NormalRightNotes[i]->GetTiming()) < HIT_TIMING)
			{
				if (fabs(NormalRightNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = NormalRightNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// ノーツエフェクト
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(NormalRightNotes[Quick]->GetLaneNum());
				break;
			}
			NormalScoreAdd(timing);
			NormalRightNotes[Quick]->SetUseFlag(false);
			ComboAdd();
			CLane::getInstance()->NotesEffect(NormalRightNotes[Quick]->GetLaneNum(), NormalRightNotes[Quick]->GetLaneType());
		}
	}
	// 右ノーマルロングノーツ
	if (CInput::GetKeyboardData(DIK_C, PRESS) || CInput::GetKeyboardData(DIK_V, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
		{
			// ノーツが生きているか
			if (!(*it)->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				// 一致していれば抜ける
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// 一致せず抜けていれば戻る
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// スコア加算やなんやかんや
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// ノーツエフェクト
					for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
					{
						if ((*it2)->GetUseFlag())
							continue;
						(*it2)->Create((*it)->GetLaneNum());
					}
				}
				else
				{
					CLane::getInstance()->TimerReset((*it)->GetLaneNum(), (*it)->GetLaneType());
				}
			}
		}
	}

	// 左クリックノーツ
	if (CInput::GetMouseData(Mouse_Data::L_BUTTON, TRIGGER))
	{
		int Quick = -1;// 一番速いノーツの番号
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L]; i++)
		{
			// ノーツが生きているか
			if (!ClickLeftNotes[i]->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				if (ClickLeftNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if (fabs(ClickLeftNotes[i]->GetTiming()) < HIT_TIMING)
			{
				if (fabs(ClickLeftNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = ClickLeftNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// ノーツエフェクト
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(ClickLeftNotes[Quick]->GetLaneNum());
				break;
			}
			NormalScoreAdd(timing);
			ClickLeftNotes[Quick]->SetUseFlag(false);
			ComboAdd();
			CLane::getInstance()->NotesEffect(ClickLeftNotes[Quick]->GetLaneNum(), ClickLeftNotes[Quick]->GetLaneType());
		}
	}
	// 左クリックロングノーツ
	if (CInput::GetMouseData(Mouse_Data::L_BUTTON, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
		{
			// ノーツが生きているか
			if (!(*it)->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				// 一致していれば抜ける
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// 一致せず抜けていれば戻る
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// スコア加算やなんやかんや
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// ノーツエフェクト
					for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
					{
						if ((*it2)->GetUseFlag())
							continue;
						(*it2)->Create((*it)->GetLaneNum());
					}
				}
				else
				{
					CLane::getInstance()->TimerReset((*it)->GetLaneNum(), (*it)->GetLaneType());
				}
			}
		}
	}

	// 右クリックノーツ
	if (CInput::GetMouseData(Mouse_Data::R_BUTTON, TRIGGER))
	{
		int Quick = -1;// 一番速いノーツの番号
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R]; i++)
		{
			// ノーツが生きているか
			if (!ClickRightNotes[i]->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				if (ClickRightNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if (fabs(ClickRightNotes[i]->GetTiming()) < HIT_TIMING)
			{
				if (fabs(ClickRightNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = ClickRightNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// ノーツエフェクト
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(ClickRightNotes[Quick]->GetLaneNum());
				break;
			}
			NormalScoreAdd(timing);
			ClickRightNotes[Quick]->SetUseFlag(false);
			ComboAdd();
			CLane::getInstance()->NotesEffect(ClickRightNotes[Quick]->GetLaneNum(), ClickRightNotes[Quick]->GetLaneType());
		}
	}
	// 右クリックロングノーツ
	if (CInput::GetMouseData(Mouse_Data::R_BUTTON, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
		{
			// ノーツが生きているか
			if (!(*it)->GetUseFlag())
				continue;
			// レーンが一致しているか
			for (j = Up; j <= Down; j++)
			{
				// 一致していれば抜ける
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// 一致せず抜けていれば戻る
			if (j > Down)
				continue;

			// 判定タイミングに入っているか
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// スコア加算やなんやかんや
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// ノーツエフェクト
					for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
					{
						if ((*it2)->GetUseFlag())
							continue;
						(*it2)->Create((*it)->GetLaneNum());
					}
				}
				else
				{
					CLane::getInstance()->TimerReset((*it)->GetLaneNum(), (*it)->GetLaneType());
				}
			}
		}
	}

	// 上ホイールノーツ
	if (CInput::GetMouseWheel() > 0)
	{
		int Quick = -1;// 一番速いノーツの番号
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_U]; i++)
		{
			// ノーツが生きているか
			if (!WheelUpNotes[i]->GetUseFlag())
				continue;
			// レーンが一致しているか

			// 判定タイミングに入っているか
			if (fabs(WheelUpNotes[i]->GetTiming()) < HIT_TIMING)
			{
				if (fabs(WheelUpNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = WheelUpNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// ノーツエフェクト
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(-1);
				break;
			}
			NormalScoreAdd(timing);
			WheelUpNotes[Quick]->SetUseFlag(false);
			ComboAdd();
		}
	}
	// 下ホイールノーツ
	if (CInput::GetMouseWheel() < 0)
	{
		int Quick = -1;// 一番速いノーツの番号
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_D]; i++)
		{
			// ノーツが生きているか
			if (!WheelDownNotes[i]->GetUseFlag())
				continue;
			// レーンが一致しているか


			// 判定タイミングに入っているか
			if (fabs(WheelDownNotes[i]->GetTiming()) < HIT_TIMING)
			{
				if (fabs(WheelDownNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = WheelDownNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// ノーツエフェクト
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(LANE_NUM);
				break;
			}
			NormalScoreAdd(timing);
			WheelDownNotes[Quick]->SetUseFlag(false);
			ComboAdd();
		}
	}
}

// スコア加算関数
void CNotesMgr::NormalScoreAdd(double timing)
{
	if (fabs(timing) < PERFECT_TIMING)
	{

		Score += 1000;
	}
	else if (fabs(timing) < GREAT_TIMING)
	{
		Score += 500;
		if (timing < 0)
		{// 速い！
			GreatQuickCount++;
			NotesDecision.Active(DECISION_FAST);
			//mPlayDataMgr->SetPlayData(, GreatQuickCount)
		}
		else
		{// 遅い！
			GreatSlowCount++;
			NotesDecision.Active(DECISION_SLOW);
		}
	}
	else if (fabs(timing) < GOOD_TIMING)
	{
		NowCombo = 0;	// コンボ数初期化！
		Score += 300;
		if (timing < 0)
		{// 速い！
			GoodQuickCount++;
			NotesDecision.Active(DECISION_FAST);
		}
		else
		{// 遅い！
			GoodSlowCount++;
			NotesDecision.Active(DECISION_SLOW);
		}
	}
	else
	{
		MissCount++;
		NowCombo = 0;// コンボ数初期化
		Score += 100;
	}
	mPlayDataMgr->SetPlayData(eData_Score, Score);
}

// コンボ加算関数
void CNotesMgr::ComboAdd()
{
	NowCombo++;
	if (MaxCombo < NowCombo)
	{
		MaxCombo = NowCombo;
		mPlayDataMgr->SetPlayData(eData_MaxCombo, MaxCombo);
	}
	mPlayDataMgr->SetPlayData(eData_NowCombo, NowCombo);
}

// 選択レーン更新関数
void CNotesMgr::SetSelectLane(deque<int> selectLane)
{
	SelectLane.clear();
	SelectLane = selectLane;
}

// 楽曲終了確認関数
bool CNotesMgr::SoundEndCheck()
{
	return SoundEndFlag;
}