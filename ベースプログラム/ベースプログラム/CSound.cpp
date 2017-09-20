//***********************************************************************************************************
//
// サウンドクラス
//
//***********************************************************************************************************


//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CSound.h"


//***********************************************************************************************************
// 初期化処理
//***********************************************************************************************************
HRESULT CSound::Init(char* BGM)
{
	HRESULT			hr;
	HWND hWnd = CWindowAPI::GethWnd();

	lpDirectSounds = NULL;
	lpPrimary = NULL;
	lpSecondary = NULL;

	// DirectSound8を作成
	if (FAILED(hr = DirectSoundCreate8(NULL, &lpDirectSounds, NULL)))
	{	// サウンドオブジェクト作成失敗
		MessageBox(hWnd, "サウンドオブジェクト作成失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 強調モード設定
	if (FAILED(hr = lpDirectSounds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY)))
	{	// 強調モード設定失敗
		MessageBox(hWnd, "強調モード設定失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// プライマリサウンドバッファの作成
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));

	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;

	// プライマリサウンドバッファ作成
	if (FAILED(hr = lpDirectSounds->CreateSoundBuffer(&dsdesc, &lpPrimary, NULL)))
	{	// プライマリサウンドバッファ作成失敗
		MessageBox(hWnd, "プライマリサウンドバッファ作成失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// プライマリバッファのステータスを決定
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;

	// プライマリバッファのステータス設定
	if (FAILED(hr = lpPrimary->SetFormat(&wf)))
	{	// プライマリバッファのステータス設定失敗
		MessageBox(hWnd, "プライマリバッファのステータス設定失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	m_bPlayNow = false;
	m_bPlayed = false;

	// WAVファイルをロード
	HMMIO hSrc;

	MMCKINFO	mSrcWaveFile;
	MMCKINFO	mSrcWaveFmt;
	MMCKINFO	mSrcWaveData;

	hSrc = mmioOpen(BGM, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);

	// 'WAVE'チャンクチェック
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	if (FAILED(hr = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF)))
	{	// 'WAVE'チャンクチェックエラー
		MessageBox(hWnd, "'WAVE'チャンクチェックエラー", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 'fmt 'チャンクチェック
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	if (FAILED(hr = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK)))
	{	// 'fmt 'チャンクチェックエラー
		MessageBox(hWnd, "'fmt 'チャンクチェックエラー", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ヘッダサイズの計算
	int iSrcHeaderSize = mSrcWaveFmt.cksize;

	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// ヘッダメモリ確保
	Wave_Format = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);

	// WAVEフォーマットのロード
	ZeroMemory(Wave_Format, iSrcHeaderSize);
	if (FAILED(hr = mmioRead(hSrc, (char*)Wave_Format, mSrcWaveFmt.cksize)))
	{	// WAVEフォーマットのロード
		MessageBox(hWnd, "WAVEフォーマットのロードエラー", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// dataチャンクを探す
	while (1)
	{
		// 検索
		hr = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);

		if (mSrcWaveData.ckid == mmioStringToFOURCC("data", 0))
			break;

		// 次のチャンクへ
		hr = mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	// サウンドバッファの作成
	ZeroMemory(&dsDesc, sizeof(DSBUFFERDESC));

	dsDesc.dwSize = sizeof(DSBUFFERDESC);
	dsDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	dsDesc.dwBufferBytes = mSrcWaveData.cksize;
	dsDesc.lpwfxFormat = Wave_Format;
	dsDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	if (FAILED(hr = lpDirectSounds->CreateSoundBuffer(&dsDesc, &lpSecondary, NULL)))
	{	// サウンドバッファの作成失敗
		MessageBox(hWnd, "サウンドバッファの作成失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ロック開始
	LPVOID	pMem1, pMem2;
	DWORD	dwSize1, dwSize2;

	if (FAILED(hr = lpSecondary->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
	{	// ロック失敗
		MessageBox(hWnd, "ロック失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ロック解除
	if (FAILED(hr = lpSecondary->Unlock(pMem1, dwSize1, pMem2, dwSize2)))
	{	// ロック解除失敗
		MessageBox(hWnd, "ロック解除失敗", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ヘッダ用メモリを開放
	free(Wave_Format);

	// WAVを閉じる
	mmioClose(hSrc, 0);

	return S_OK;
}

//***********************************************************************************************************
// 終了処理
//***********************************************************************************************************
void CSound::Finalise()
{
	if (lpSecondary != NULL)
	{
		lpSecondary->Release();
		lpSecondary = NULL;
	}

	if (lpPrimary != NULL)
	{
		lpPrimary->Release();
		lpPrimary = NULL;
	}

	if (lpDirectSounds != NULL)
	{
		lpDirectSounds->Release();
		lpDirectSounds = NULL;
	}
}

//***********************************************************************************************************
// 再生
//***********************************************************************************************************
HRESULT CSound::Play(bool bLoopFlg)
{
	HRESULT			hr;
	HWND hWnd = CWindowAPI::GethWnd();

	if (m_bPlayNow)
	{// 再生中なら再生位置を最初に戻す
		return E_FAIL;// 何もしない！
					  //lpSecondary->SetCurrentPosition(0);
					  //m_bPlayed = false;
	}
	else
	{// 再生していなければ音再生
		if (FAILED(hr = lpSecondary->Play(0, 0, bLoopFlg)))
		{	// 再生失敗
			MessageBox(hWnd, "音楽再生失敗", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		m_bPlayNow = true;
	}

	return S_OK;
}

//***********************************************************************************************************
// 停止
//***********************************************************************************************************
void CSound::Stop()
{
	if (m_bPlayNow)
	{
		lpSecondary->Stop();
		m_bPlayNow = false;
		m_bPlayed = true;
	}
}

//***********************************************************************************************************
// BGMを先頭まで巻き戻し
//***********************************************************************************************************
void CSound::StartSet()
{
	if (m_bPlayed)
	{
		lpSecondary->SetCurrentPosition(0);
		m_bPlayed = false;
	}
}

//***********************************************************************************************************
// 音量調節
//***********************************************************************************************************
void CSound::Change_Volume(LONG volume)
{

	if (volume < DSBVOLUME_MIN)
	{
		volume = DSBVOLUME_MIN;
	}
	else
		if (volume > DSBVOLUME_MAX)
		{
			volume = DSBVOLUME_MAX;
		}
	//! ボリューム設定を変更する.
	lpSecondary->SetVolume(volume);

	//if (m_bPlayed)
	//{
	//	lpSecondary->SetVolume(volume);
	//}
}

// 指定time(s)にカレント位置を移動
void CSound::SetCurrentPosition(double time)
{
	DWORD SetTime = (DWORD)((float)(wf.nSamplesPerSec * wf.nChannels * wf.wBitsPerSample / 8) * time);
	lpSecondary->SetCurrentPosition(SetTime);
}

// サウンドファイルの長さを秒数で取得
int CSound::GetSoundFileLength()
{
	return dsDesc.dwBufferBytes / (wf.nSamplesPerSec * wf.nChannels * wf.wBitsPerSample / 8);
}

// 現在の再生時間を取得
double CSound::GetNowPlayTime()
{
	DWORD NowByte = 0;
	lpSecondary->GetCurrentPosition(&NowByte, NULL);
	int SecByte = (wf.nSamplesPerSec * wf.nChannels * wf.wBitsPerSample / 8);
	double NowTime = (double)NowByte / SecByte;
	return NowTime;
}

void CSound::PositionBack()
{
	lpSecondary->SetCurrentPosition(dsDesc.dwBufferBytes);
}

// 現在の状態を取得
DWORD CSound::GetStatus()
{
	Status = 0;
	lpSecondary->GetStatus(&Status);
	return Status;
}

bool CSound::GetPlaying()
{
	HRESULT hr;

	Status = 0;
	hr = lpSecondary->GetStatus(&Status);
	if (hr == S_OK)
	{
		if (Status == DSBSTATUS_PLAYING)
			return true;
	}
	return false;
}

DWORD CSound::GetCurrentPosition()
{
	DWORD dw1, dw2;
	lpSecondary->GetCurrentPosition(&dw1, &dw2);
	return dw1;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************