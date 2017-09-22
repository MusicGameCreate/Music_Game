// 楽曲情報とノーツ情報を読み込むクラス
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string>
#include<deque>

using namespace std;

// ノーツリスト列挙体
enum
{
	NOTES_LIST_NORMAL_L,
	NOTES_LIST_NORMAL_L_LONG,
	NOTES_LIST_NORMAL_R,
	NOTES_LIST_NORMAL_R_LONG,
	NOTES_LIST_CLICK_L,
	NOTES_LIST_CLICK_L_LONG,
	NOTES_LIST_CLICK_R,
	NOTES_LIST_CLICK_R_LONG,
	NOTES_LIST_WHEEL_U,
	NOTES_LIST_WHEEL_D,

	NOTES_LIST_MAX
};

//// 譜面取得用列挙体
//enum _NOTES_TYPE
//{
//	NOTES_READ_NORMAL_L,
//	NOTES_READ_NORMAL_R,
//	NOTES_READ_CLICK_L,
//	NOTES_READ_CLICK_R,
//	NOTES_READ_WHEEL,
//
//	NOTES_READ_MAX
//};

// 楽曲データ列挙体
enum _MUSIC_DATA_LIST
{
	TITLE_NAME,
	ARTIST_NAME,
	CREATOR_NAME,
	JACKET_PASS,
	ILLUSTRATOR_NAME,
	DIFFICULTY,
	LEVEL,
	BPM,
	MUSIC_PASS,
	MUSIC_VOLUME,
	ST,
	PST,
	PLE,
	BG,
	BGA,

	MUSIC_DATA_MAX
};

// 楽曲データ構造体
typedef struct
{
	string		TitleName;			// 楽曲名
	string		ArtistName;			// 作曲者
	string		CreatorName;		// 譜面作成者
	string		JacketPass;			// ジャケットのパス
	string		IllustratorName;	// ジャケット製作者
	int			Difficulty;			// 難易度
	int			Level;				// レベル
	int			Bpm;				// BPM
	string		MusicPass;			// 楽曲のパス
	int			Volume;				// 音量ボリューム(%)
	int			StartTiming;		// 曲の先頭タイミング
	int			Pst;				// 選曲画面の曲スタート位置
	int			Ple;				// 曲スタート位置から流す長さ
									//int		Beat[2];			// ○分の○拍子
	int			Bg;					// 背景パターン
	int			BgAnim;				// 背景アニメーション
} JacketData;

// ノーツ出現数格納構造体
typedef struct
{
	int Normal_L_Count;			// 左ノーマルノーツの数
	int Normal_L_Long_Count;	// 左ノーマルロングノーツの数
	int Normal_R_Count;			// 右ノーマルノーツの数
	int Normal_R_Long_Count;	// 右ノーマルロングノーツの数
	int Click_L_Count;			// 左クリックノーツの数
	int Click_L_Long_Count;		// 左クリックロングノーツの数
	int Click_R_Count;			// 右クリックノーツの数
	int Click_R_Long_Count;		// 右クリックロングノーツの数
	int Wheel_U_Count;			// 上ホイールノーツの数
	int Wheel_D_Count;			// 下ホイールノーツの数
	int	BeatCount;				// 16分の総合数
	int MajorCount;				// 総ノーツ数
} NotesCount;

// ノーツデータ構造体
typedef struct
{
	deque<deque<int>> Normal_L;		// 左ノーマルノーツ
	deque<deque<int>> Normal_L_Long;// 左ノーマルノーツ
	deque<deque<int>> Normal_R;		// 右ノーマルノーツ
	deque<deque<int>> Normal_R_Long;// 右ノーマルノーツ
	deque<deque<int>> Click_L;		// 左クリックノーツ
	deque<deque<int>> Click_L_Long;	// 左クリックノーツ
	deque<deque<int>> Click_R;		// 右クリックノーツ
	deque<deque<int>> Click_R_Long;	// 右クリックノーツ
	deque<deque<int>> Wheel_U;		// ホイールノーツ
	deque<deque<int>> Wheel_D;		// ホイールノーツ
	NotesCount NotesCount;			// ノーツ毎の出現数カウント
} NotesData;

// 楽曲データ構造体
typedef struct
{
	JacketData	Jacket;
	NotesData	Notes;				// ノーツデータ
} MusicData;

// 楽曲情報読み取りクラス
class CMusicDataReader
{
private:
	MusicData	m_MusicData;		// 楽曲データ

									//void NotesDataLoad();
									//void MusicDataLoad();
public:
	CMusicDataReader();
	~CMusicDataReader();

	// 指定ファイルの情報と譜面情報を読み込む
	void MusicDataLoad(string fileName);
	// 指定ファイルのジャケット情報のみ読み込む
	void JacketFileLoad(string fileName, FILE* fp = NULL);
	// 楽曲情報を返す
	inline const MusicData* GetMusicData() { return &m_MusicData; };
	// ノーツ情報を返す
	deque<int> GetNotesData(int notesType);
	// ロングの数を返して中身を消す
	int GetLongNum(int notesType);
};