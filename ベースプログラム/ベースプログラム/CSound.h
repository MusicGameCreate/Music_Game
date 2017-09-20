//***********************************************************************************************************
//
// 音情報設定クラス
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include <dsound.h>

#include "Define.h"
#include "CDirectX.h"
#include "CWindowAPI.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )

//***********************************************************************************************************
// クラス定義
//***********************************************************************************************************
class CSound
{
private:
	LPDIRECTSOUND8			lpDirectSounds;	// DirectSound8
	LPDIRECTSOUNDBUFFER		lpPrimary;		// プライマリサウンドバッファ
	LPDIRECTSOUNDBUFFER		lpSecondary;	// セカンダリサウンドバッファ
											//IDirectMusicPerformance8 i;
	WAVEFORMATEX			wf;
	DSBUFFERDESC			dsDesc;

	LPWAVEFORMATEX			Wave_Format;

	bool					m_bPlayNow;
	bool					m_bPlayed;

	DWORD	Status;

public:
	HRESULT Init(char* BGM);
	void Finalise();

	HRESULT Play(bool bLoopFlg);	// 再生(WAVデータのファイルパス、ループ再生するかどうかtrue or false, hWnd)
	void Stop();											// 一時停止
	void StartSet();										// BGMを先頭まで巻き戻し
	void Change_Volume(LONG volume);						// 音量調節
															// 指定time(s)の位置にカレント位置を移動
	void SetCurrentPosition(double time);
	// 最後尾にカレントポジションを移動
	void PositionBack();
	// サウンドファイルの長さを取得
	int GetSoundFileLength();
	// 現在の再生時間を取得
	double GetNowPlayTime();
	// 現在の状態を取得
	DWORD GetStatus();
	// 再生中か取得
	bool GetPlaying();

	DWORD GetCurrentPosition();
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************