#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "Lane.h"
#include "BaseNotes.h"
#include "LongNotes.h"
#include "WheelNotes.h"
#include "MusicDataReader.h"
#include "Debug.h"
#include "GameMain_Bar.h"
#include "CTimer.h"
#include "IPlayDataMgr.h"
#include "NotesEffect.h"
#include "NotesDecision.h"

using namespace std;

class CNotesMgr
{
private:
	CMusicDataReader	reader;			// 楽曲情報読み取り
	IPlayDataMgr*		mPlayDataMgr;	// データインターフェース
	LaneData			Data;
	NotesData			Notes;
	int					MusicNum;		// 楽曲の番号

	// スコアデータ
	int					Score;				// スコア
	int					NowCombo;			// 現在のコンボ数
	int					MaxCombo;			// 最大コンボ数
	int					PerfectCount;		// パーフェクト判定の数
	int					GreatQuickCount;	// 速いグレート判定の数
	int					GreatSlowCount;		// 遅いグレート判定の数
	int					GoodQuickCount;		// 速いグッド判定の数
	int					GoodSlowCount;		// 遅いグッド判定の数
	int					MissCount;			// ミスの数


	double				MajorBeatTime;	// 16分の時間
	double				MajorTime;		// 一小節の時間
	double				CourceTime;		// 事前配置時に最後に生成したノーツとレーンの端までにかかる時間
	double				SoundTimer;		// ノーツ生成時の再生時間
	double				EmptyTime;		// 空レーンを流す時間

	double				Bpm;			// BPM
	double				HiSpeed;		// ハイスピード
	bool				CreateFlag;

	int			NotesNum[NOTES_LIST_MAX];		// ノーツ毎の数
												//vector<CBaseNotes*>	NotesList[NOTES_LIST_MAX];
	vector<CBaseNotes*> NormalLeftNotes;
	vector<CLongNotes*> NormalLeftLongNotes;
	vector<CBaseNotes*> NormalRightNotes;
	vector<CLongNotes*> NormalRightLongNotes;
	vector<CBaseNotes*> ClickLeftNotes;
	vector<CLongNotes*> ClickLeftLongNotes;
	vector<CBaseNotes*> ClickRightNotes;
	vector<CLongNotes*> ClickRightLongNotes;
	vector<CWheelNotes*> WheelUpNotes;
	vector<CWheelNotes*> WheelDownNotes;
	//CBaseNotes*	Normal_L_Long_Notes;
	//CBaseNotes*	Normal_R_Notes;
	//CBaseNotes*	Normal_R_Long_Notes;
	//CBaseNotes*	Click_L_Notes;
	//CBaseNotes*	Click_L_Long_Notes;
	//CBaseNotes*	Click_R_Notes;
	//CBaseNotes*	Click_R_Long_Notes;
	//CBaseNotes*	Wheel_U_Notes;
	//CBaseNotes*	Wheel_D_Notes;

	deque<int>	SelectLane;		// 選択されているレーン
	vector<CNotesEffect*>	m_NotesEffect;	// ノーツを消した時のエフェクト
	CNotesDecision NotesDecision;

	bool		InitFlag;
	int			BeatCount;
	bool		EmptyFlag;
	int		InitSoundCounter;
	double		InitSoundCounterBase;
	bool		InitSoundFlag;

	//CSound sound;
	CSound*	GameMusic;
	//CSound debug;
	//GameMain_Bar bar;
	int		InitCount;
	bool	Playing;
	double	start;
	double	PlayingTime;
	double	Last;
	DWORD	dw;

	double	OverTime;

	bool	SoundEndFlag;
	double	OldSound;

	void NotesCreate(double CourseTime);	// ノーツ生成
	void NotesDecition();					// ノーツ判定
	void NormalScoreAdd(double timing);		// スコア加算
	void ComboAdd();						// コンボ数増加
	void AllSetSpeed(double bpm, double hispeed);			// 全ノーツに速度設定
public:
	CNotesMgr(IPlayDataMgr* dataMgr);
	~CNotesMgr();

	void Initialize();
	void Load();
	void Finalize();
	void Update();
	void Draw();

	void SetLaneData(LaneData data) { Data = data; }
	//void SetDataMgr(IPlayDataMgr* mgr) { mPlayDataMgr = mgr; }

	void SetSelectLane(deque<int> selectLane);

	bool SoundEndCheck();
};