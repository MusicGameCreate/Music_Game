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
	CMusicDataReader	reader;			// �y�ȏ��ǂݎ��
	IPlayDataMgr*		mPlayDataMgr;	// �f�[�^�C���^�[�t�F�[�X
	LaneData			Data;
	NotesData			Notes;
	int					MusicNum;		// �y�Ȃ̔ԍ�

	// �X�R�A�f�[�^
	int					Score;				// �X�R�A
	int					NowCombo;			// ���݂̃R���{��
	int					MaxCombo;			// �ő�R���{��
	int					PerfectCount;		// �p�[�t�F�N�g����̐�
	int					GreatQuickCount;	// �����O���[�g����̐�
	int					GreatSlowCount;		// �x���O���[�g����̐�
	int					GoodQuickCount;		// �����O�b�h����̐�
	int					GoodSlowCount;		// �x���O�b�h����̐�
	int					MissCount;			// �~�X�̐�


	double				MajorBeatTime;	// 16���̎���
	double				MajorTime;		// �ꏬ�߂̎���
	double				CourceTime;		// ���O�z�u���ɍŌ�ɐ��������m�[�c�ƃ��[���̒[�܂łɂ����鎞��
	double				SoundTimer;		// �m�[�c�������̍Đ�����
	double				EmptyTime;		// �󃌁[���𗬂�����

	double				Bpm;			// BPM
	double				HiSpeed;		// �n�C�X�s�[�h
	bool				CreateFlag;

	int			NotesNum[NOTES_LIST_MAX];		// �m�[�c���̐�
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

	deque<int>	SelectLane;		// �I������Ă��郌�[��
	vector<CNotesEffect*>	m_NotesEffect;	// �m�[�c�����������̃G�t�F�N�g
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

	void NotesCreate(double CourseTime);	// �m�[�c����
	void NotesDecition();					// �m�[�c����
	void NormalScoreAdd(double timing);		// �X�R�A���Z
	void ComboAdd();						// �R���{������
	void AllSetSpeed(double bpm, double hispeed);			// �S�m�[�c�ɑ��x�ݒ�
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