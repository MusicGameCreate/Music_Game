//***********************************************************************************************************
//
// �T�E���h�N���X
//
//***********************************************************************************************************


//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CSound.h"


//***********************************************************************************************************
// ����������
//***********************************************************************************************************
HRESULT CSound::Init(char* BGM)
{
	HRESULT			hr;
	HWND hWnd = CWindowAPI::GethWnd();

	lpDirectSounds = NULL;
	lpPrimary = NULL;
	lpSecondary = NULL;

	// DirectSound8���쐬
	if (FAILED(hr = DirectSoundCreate8(NULL, &lpDirectSounds, NULL)))
	{	// �T�E���h�I�u�W�F�N�g�쐬���s
		MessageBox(hWnd, "�T�E���h�I�u�W�F�N�g�쐬���s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h�ݒ�
	if (FAILED(hr = lpDirectSounds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY)))
	{	// �������[�h�ݒ莸�s
		MessageBox(hWnd, "�������[�h�ݒ莸�s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �v���C�}���T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));

	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;

	// �v���C�}���T�E���h�o�b�t�@�쐬
	if (FAILED(hr = lpDirectSounds->CreateSoundBuffer(&dsdesc, &lpPrimary, NULL)))
	{	// �v���C�}���T�E���h�o�b�t�@�쐬���s
		MessageBox(hWnd, "�v���C�}���T�E���h�o�b�t�@�쐬���s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �v���C�}���o�b�t�@�̃X�e�[�^�X������
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;

	// �v���C�}���o�b�t�@�̃X�e�[�^�X�ݒ�
	if (FAILED(hr = lpPrimary->SetFormat(&wf)))
	{	// �v���C�}���o�b�t�@�̃X�e�[�^�X�ݒ莸�s
		MessageBox(hWnd, "�v���C�}���o�b�t�@�̃X�e�[�^�X�ݒ莸�s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	m_bPlayNow = false;
	m_bPlayed = false;

	// WAV�t�@�C�������[�h
	HMMIO hSrc;

	MMCKINFO	mSrcWaveFile;
	MMCKINFO	mSrcWaveFmt;
	MMCKINFO	mSrcWaveData;

	hSrc = mmioOpen(BGM, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);

	// 'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	if (FAILED(hr = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF)))
	{	// 'WAVE'�`�����N�`�F�b�N�G���[
		MessageBox(hWnd, "'WAVE'�`�����N�`�F�b�N�G���[", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// 'fmt '�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	if (FAILED(hr = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK)))
	{	// 'fmt '�`�����N�`�F�b�N�G���[
		MessageBox(hWnd, "'fmt '�`�����N�`�F�b�N�G���[", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;

	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// �w�b�_�������m��
	Wave_Format = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	ZeroMemory(Wave_Format, iSrcHeaderSize);
	if (FAILED(hr = mmioRead(hSrc, (char*)Wave_Format, mSrcWaveFmt.cksize)))
	{	// WAVE�t�H�[�}�b�g�̃��[�h
		MessageBox(hWnd, "WAVE�t�H�[�}�b�g�̃��[�h�G���[", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// data�`�����N��T��
	while (1)
	{
		// ����
		hr = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);

		if (mSrcWaveData.ckid == mmioStringToFOURCC("data", 0))
			break;

		// ���̃`�����N��
		hr = mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	// �T�E���h�o�b�t�@�̍쐬
	ZeroMemory(&dsDesc, sizeof(DSBUFFERDESC));

	dsDesc.dwSize = sizeof(DSBUFFERDESC);
	dsDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	dsDesc.dwBufferBytes = mSrcWaveData.cksize;
	dsDesc.lpwfxFormat = Wave_Format;
	dsDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	if (FAILED(hr = lpDirectSounds->CreateSoundBuffer(&dsDesc, &lpSecondary, NULL)))
	{	// �T�E���h�o�b�t�@�̍쐬���s
		MessageBox(hWnd, "�T�E���h�o�b�t�@�̍쐬���s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// ���b�N�J�n
	LPVOID	pMem1, pMem2;
	DWORD	dwSize1, dwSize2;

	if (FAILED(hr = lpSecondary->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
	{	// ���b�N���s
		MessageBox(hWnd, "���b�N���s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ���b�N����
	if (FAILED(hr = lpSecondary->Unlock(pMem1, dwSize1, pMem2, dwSize2)))
	{	// ���b�N�������s
		MessageBox(hWnd, "���b�N�������s", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �w�b�_�p���������J��
	free(Wave_Format);

	// WAV�����
	mmioClose(hSrc, 0);

	return S_OK;
}

//***********************************************************************************************************
// �I������
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
// �Đ�
//***********************************************************************************************************
HRESULT CSound::Play(bool bLoopFlg)
{
	HRESULT			hr;
	HWND hWnd = CWindowAPI::GethWnd();

	if (m_bPlayNow)
	{// �Đ����Ȃ�Đ��ʒu���ŏ��ɖ߂�
		return E_FAIL;// �������Ȃ��I
					  //lpSecondary->SetCurrentPosition(0);
					  //m_bPlayed = false;
	}
	else
	{// �Đ����Ă��Ȃ���Ή��Đ�
		if (FAILED(hr = lpSecondary->Play(0, 0, bLoopFlg)))
		{	// �Đ����s
			MessageBox(hWnd, "���y�Đ����s", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		m_bPlayNow = true;
	}

	return S_OK;
}

//***********************************************************************************************************
// ��~
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
// BGM��擪�܂Ŋ����߂�
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
// ���ʒ���
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
	//! �{�����[���ݒ��ύX����.
	lpSecondary->SetVolume(volume);

	//if (m_bPlayed)
	//{
	//	lpSecondary->SetVolume(volume);
	//}
}

// �w��time(s)�ɃJ�����g�ʒu���ړ�
void CSound::SetCurrentPosition(double time)
{
	DWORD SetTime = (DWORD)((float)(wf.nSamplesPerSec * wf.nChannels * wf.wBitsPerSample / 8) * time);
	lpSecondary->SetCurrentPosition(SetTime);
}

// �T�E���h�t�@�C���̒�����b���Ŏ擾
int CSound::GetSoundFileLength()
{
	return dsDesc.dwBufferBytes / (wf.nSamplesPerSec * wf.nChannels * wf.wBitsPerSample / 8);
}

// ���݂̍Đ����Ԃ��擾
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

// ���݂̏�Ԃ��擾
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