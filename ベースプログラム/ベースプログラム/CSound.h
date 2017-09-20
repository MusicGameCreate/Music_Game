//***********************************************************************************************************
//
// �����ݒ�N���X
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include <dsound.h>

#include "Define.h"
#include "CDirectX.h"
#include "CWindowAPI.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )

//***********************************************************************************************************
// �N���X��`
//***********************************************************************************************************
class CSound
{
private:
	LPDIRECTSOUND8			lpDirectSounds;	// DirectSound8
	LPDIRECTSOUNDBUFFER		lpPrimary;		// �v���C�}���T�E���h�o�b�t�@
	LPDIRECTSOUNDBUFFER		lpSecondary;	// �Z�J���_���T�E���h�o�b�t�@
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

	HRESULT Play(bool bLoopFlg);	// �Đ�(WAV�f�[�^�̃t�@�C���p�X�A���[�v�Đ����邩�ǂ���true or false, hWnd)
	void Stop();											// �ꎞ��~
	void StartSet();										// BGM��擪�܂Ŋ����߂�
	void Change_Volume(LONG volume);						// ���ʒ���
															// �w��time(s)�̈ʒu�ɃJ�����g�ʒu���ړ�
	void SetCurrentPosition(double time);
	// �Ō���ɃJ�����g�|�W�V�������ړ�
	void PositionBack();
	// �T�E���h�t�@�C���̒������擾
	int GetSoundFileLength();
	// ���݂̍Đ����Ԃ��擾
	double GetNowPlayTime();
	// ���݂̏�Ԃ��擾
	DWORD GetStatus();
	// �Đ������擾
	bool GetPlaying();

	DWORD GetCurrentPosition();
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************