#include "NotesMgr.h"
#include "TimeServer.h"
#include "CMusic_Manager.h"

//#include <boost/bind.hpp>
//#include <boost/thread.hpp>

//using namespace boost;

const int InitEmptyLane = 2;	// �ŏ��ɗ����󃌁[���̒���

// �R���X�g���N�^
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

// �f�X�g���N�^
CNotesMgr::~CNotesMgr()
{
	//Finalize();
}

// �������֐�
void CNotesMgr::Initialize()
{
	CNotesMgr::Load();
}

// �f�[�^�ǂݍ��݊֐�
void CNotesMgr::Load()
{
	// �T�E���h�ǂݍ���
	GameMusic = new CSound;
	GameMusic->Init(CMusic_Manager::Get_MusicData(MusicNum)->Music_Path);
	//GameMusic->Init("../DATA/MUSIC/badapple.music/badapple.wav");
	//GameMusic->Init("../DATA/MUSIC/LemonadeParty.music/LemonadeParty.wav");// �����œn���ꂽ�Ȃ̃p�X�ɃA�N�Z�X
	//Playing = GameMusic->GetPlaying();
	//start = GameMusic->GetStatus();
	//start = (double)clock() / CLOCKS_PER_SEC;
	//Playing = GameMusic->GetPlaying();

	// �ϐ�������
	for (int i = 0; i < 6; i++)
	{
		NotesNum[i] = 0;
	}
	//nCount = 0;
	BeatCount = 0;

	// ���ʓǂݍ���
	reader.MusicDataLoad(CMusic_Manager::Get_MusicData(MusicNum)->Fumen_Path[mPlayDataMgr->GetPlayData(eData_Difficult)]);
	//reader.FileRead("../DATA/TEXT/sample.score");
	//reader.FileRead("../DATA/MUSIC/LemonadeParty.music/lemon_E.score");// �����œn���ꂽ���ʂ̃p�X�ɃA�N�Z�X
	//reader.FileRead("../DATA/MUSIC/LemonadeParty.music/lemon.score");// �����œn���ꂽ���ʂ̃p�X�ɃA�N�Z�X


	//GameMusic->Play(false);
	//GameMusic->Change_Volume(-10000);
	//GameMusic->SetCurrentPosition(GameMusic->GetSoundFileLength());

	// �n�C�X�s����
	Bpm = reader.GetMusicData()->Jacket.Bpm;			// BPM�i�[
	HiSpeed = 1.0f;								// �v���C���[���ݒ肵���n�C�X�s����

	MajorBeatTime = 60.0f / (double)Bpm / 4.0f;	// 16���̎���
	MajorTime = MajorBeatTime * 16.0f;			// �ꏬ�߂̎���

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

	//normal_L.Initialize("../DATA/TEXTURE/GameMain/Notes/���m�[�c.png", Data);

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
	// ���m�[�}��
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L]; i++)
	{
		NormalLeftNotes.push_back(new CBaseNotes());
		NormalLeftNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/���m�[�c.png", Data);
	}

	// ���m�[�}�������O
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L_LONG]; i++)
	{
		NormalLeftLongNotes.push_back(new CLongNotes());
		NormalLeftLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/�����O�ԉ�.png", Data);
	}

	// �E�m�[�}��
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R]; i++)
	{
		NormalRightNotes.push_back(new CBaseNotes());
		NormalRightNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/���m�[�c.png", Data);
	}

	// �E�m�[�}�������O
	for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R_LONG]; i++)
	{
		NormalRightLongNotes.push_back(new CLongNotes());
		NormalRightLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/�����O�ԉ�.png", Data);
	}

	// ���N���b�N
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L]; i++)
	{
		ClickLeftNotes.push_back(new CBaseNotes());
		ClickLeftNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/���΃m�[�c.png", Data);
	}

	// ���N���b�N�����O
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L_LONG]; i++)
	{
		ClickLeftLongNotes.push_back(new CLongNotes());
		ClickLeftLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/�����O�ԉ���.png", Data);
	}

	// �E�N���b�N
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R]; i++)
	{
		ClickRightNotes.push_back(new CBaseNotes());
		ClickRightNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/���΃m�[�c.png", Data);
	}

	// �E�N���b�N�����O
	for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R_LONG]; i++)
	{
		ClickRightLongNotes.push_back(new CLongNotes());
		ClickRightLongNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/�����O�ԉ���.png", Data);
	}

	// ��z�C�[��
	for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_U]; i++)
	{
		WheelUpNotes.push_back(new CWheelNotes());
		WheelUpNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/�������.png", Data);
	}

	// ���z�C�[��
	for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_D]; i++)
	{
		WheelDownNotes.push_back(new CWheelNotes());
		WheelDownNotes[i]->Initialize("../DATA/TEXTURE/GameMain/Notes/��������.png", Data);
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

// �I���֐�
void CNotesMgr::Finalize()
{
	// ���m�[�}��
	for (vector<CBaseNotes*>::iterator it = NormalLeftNotes.begin(); it != NormalLeftNotes.end(); it++)
	{
		delete (*it);
	}

	// ���m�[�}�������O
	for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
	{
		delete (*it);
	}

	// �E�m�[�}��
	for (vector<CBaseNotes*>::iterator it = NormalRightNotes.begin(); it != NormalRightNotes.end(); it++)
	{
		delete (*it);
	}

	// �E�m�[�}�������O
	for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
	{
		delete (*it);
	}

	// ���N���b�N
	for (vector<CBaseNotes*>::iterator it = ClickLeftNotes.begin(); it != ClickLeftNotes.end(); it++)
	{
		delete (*it);
	}

	// ���N���b�N�����O
	for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
	{
		delete (*it);
	}

	// �E�N���b�N
	for (vector<CBaseNotes*>::iterator it = ClickRightNotes.begin(); it != ClickRightNotes.end(); it++)
	{
		delete (*it);
	}

	// �E�N���b�N�����O
	for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
	{
		delete (*it);
	}

	// ��z�C�[��
	for (vector<CWheelNotes*>::iterator it = WheelUpNotes.begin(); it != WheelUpNotes.end(); it++)
	{
		delete (*it);
	}

	// ���z�C�[��
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

// �X�V�֐�
void CNotesMgr::Update()
{
	// �Ȃ��Đ����ɂȂ�܂őҋ@
	if (!Playing)
	{
		DWORD status;
		status = GameMusic->GetStatus();
		//PlayingTime = clock() / CLOCKS_PER_SEC;
		//Last = PlayingTime - start;
		if (status == 17/* && InitCount == 0*/)
		{// �Đ����
		 // ���O�Ƀm�[�c��z�u����
			int Cnt = 0;
			double BpmSize = ((Bpm * HiSpeed) * BPM_SPEED);				// 1�b�ԂŐi�ދ���
			double MajorSize = BpmSize * (MajorTime * InitEmptyLane);	// 2���߂̎��ԂŐi�ދ���
			double MajorBeatSize = (BpmSize * MajorBeatTime);				// 16���̎��ԂŐi�ދ���
			double LifeTime = (Data.m_vTexSize.x * HiSpeed) / BpmSize;	// ���[���̒[����[�܂łɂ����鎞��

																		// 2���߂Ői�ދ��������[���̒������Z���ꍇ�͉�ʂɉf�镪�̃m�[�c���ɔz�u����B
			if (Data.m_vTexSize.x >= MajorSize)
			{
				EmptyFlag = false;
				// �z�u�ʒu�����[���̒����𒴂���܂Ŕz�u��������
				for (Cnt = 0; Data.m_vTexSize.x >= MajorSize + (MajorBeatSize * Cnt); Cnt++)
				{
					// �ʏ�̐����ʒu����ǂꂾ������Ă��邩�v�Z���Ĉ����ɓn��
					CourceTime = (((Data.m_vTexSize.x * HiSpeed) - MajorSize) - (MajorBeatSize * Cnt)) / (Data.m_vTexSize.x * HiSpeed);
					NotesCreate(LifeTime * CourceTime);
					//NotesCreate(((Data.m_vTexSize.x - MajorSize) / Data.m_vTexSize.x) )
				}
				// �z�u���I������Ɍ��Ԃ�����Ȃ珉�����炠�钴�ߎ��ԂƂ��ĕۑ�
				//CourceTime = ((Data.m_vTexSize.x - MajorSize) - (BpmSize * (MajorBeatTime * Cnt))) / Data.m_vTexSize.x;
			}
			else
			{// 2���߂̎��ԂŐi�ދ��������[���̒�����蒷���ꍇ�́A�c�艽�b�҂Ă�2���߂̎��ԂɂȂ邩�v�Z����
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
			EmptyTime += addTime;// �O�t���[������̌o�ߎ��Ԃ����Z
			InitSoundCounterBase += addTime;
			if (EmptyTime + CourceTime >= MajorBeatTime)// 16���̐�������
			{
				EmptyTime -= MajorBeatTime;
				NotesCreate(EmptyTime);
				InitSoundCounter++;
			}

			// �����x������您������������������������
			if (OverTime)
			{
				if (InitSoundCounterBase + ((MajorTime * InitEmptyLane) - OverTime) >= (MajorTime * InitEmptyLane) - (0.6f))// �Ȃ�Ƃ����킹��
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
				if (InitSoundCounterBase >= (MajorTime * InitEmptyLane) - (0.6f))// �Ȃ�Ƃ����킹��
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

		// �m�[�c����
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

		// ���̃m�[�c�𐶐��o����悤�ɂ���
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
	{// EmptyFlag == true�̏ꍇ�m�[�c�������n�܂�܂ŋ󃌁[���Đ�
		EmptyTime += addTime;

		//// �m�[�c����
		//if (EmptyTime + CourceTime >= MajorBeatTime)
		//{
		//	NotesCreate(((NowSound - SoundTimer) * HiSpeed) - MajorBeatTime);
		//}

		// 2���ߕ��̒��������[���̒[�܂ŗ�����m�[�c�Đ����s���B
		if (EmptyTime >= (MajorTime * (InitEmptyLane)))
		{
			EmptyFlag = false;
			EmptyTime -= (MajorTime * (InitEmptyLane))/* - (MajorBeatTime * 2)*/;
			NotesCreate(EmptyTime);
		}

		//EmptyTime += addTime;
	}

	OldSound = NowSound;

	//// �m�[�c�X�V
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

	// ---�m�[�c�X�V---
	// ���m�[�}��
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

	// ���m�[�}�������O
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

	// �E�m�[�}��
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

	// �E�m�[�}�������O
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

	// ���N���b�N
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

	// ���N���b�N�����O
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

	// �E�N���b�N
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

	// �E�N���b�N�����O
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

	// ��z�C�[��
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

	// ���z�C�[��
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

	// �m�[�c�G�t�F�N�g
	for (vector<CNotesEffect*>::iterator it = m_NotesEffect.begin(); it != m_NotesEffect.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Update();
	}

	NotesDecision.Update();

	// �m�[�c����
	NotesDecition();

	mPlayDataMgr->SetPlayData(eData_MaxCombo, NowCombo);
}

// �`��֐�
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


	// ���m�[�}��
	for (vector<CBaseNotes*>::iterator it = NormalLeftNotes.begin(); it != NormalLeftNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// ���m�[�}�������O
	for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// �E�m�[�}��
	for (vector<CBaseNotes*>::iterator it = NormalRightNotes.begin(); it != NormalRightNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// �E�m�[�}�������O
	for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// ���N���b�N
	for (vector<CBaseNotes*>::iterator it = ClickLeftNotes.begin(); it != ClickLeftNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// ���N���b�N�����O
	for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// �E�N���b�N
	for (vector<CBaseNotes*>::iterator it = ClickRightNotes.begin(); it != ClickRightNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// �E�N���b�N�����O
	for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// ��z�C�[��
	for (vector<CWheelNotes*>::iterator it = WheelUpNotes.begin(); it != WheelUpNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// ���z�C�[��
	for (vector<CWheelNotes*>::iterator it = WheelDownNotes.begin(); it != WheelDownNotes.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	// �m�[�c�G�t�F�N�g
	for (vector<CNotesEffect*>::iterator it = m_NotesEffect.begin(); it != m_NotesEffect.end(); it++)
	{
		if (!(*it)->GetUseFlag())
			continue;
		(*it)->Draw();
	}

	NotesDecision.Draw();
}

// ���x�ݒ�֐�
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

// �m�[�c�����֐�
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

	// ���m�[�}���m�[�c
	for (deque<int>::iterator it = Normal_L.begin(); it != Normal_L.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// �m�[�}���m�[�c
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
	// �������O�m�[�}���m�[�c
	for (deque<int>::iterator it = Normal_L_Long.begin(); it != Normal_L_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// �����O�m�[�c
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
	// �E�m�[�}���m�[�c
	for (deque<int>::iterator it = Normal_R.begin(); it != Normal_R.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// �m�[�}���m�[�c
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
	// �E�m�[�}�������O�m�[�c
	for (deque<int>::iterator it = Normal_R_Long.begin(); it != Normal_R_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// �����O�m�[�c
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
	// ���N���b�N�m�[�c
	for (deque<int>::iterator it = Click_L.begin(); it != Click_L.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// �m�[�}���m�[�c
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
	// ���N���b�N�����O�m�[�c
	for (deque<int>::iterator it = Click_L_Long.begin(); it != Click_L_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// �����O�m�[�c
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
	// �E�N���b�N�m�[�c
	for (deque<int>::iterator it = Click_R.begin(); it != Click_R.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// �m�[�}���m�[�c
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
	// �E�N���b�N�����O�m�[�c
	for (deque<int>::iterator it = Click_R_Long.begin(); it != Click_R_Long.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// �����O�m�[�c
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
	// ��z�C�[���m�[�c
	for (deque<int>::iterator it = Wheel_U.begin(); it != Wheel_U.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 1:	// �ヌ�[��
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
	// ���z�C�[���m�[�c
	for (deque<int>::iterator it = Wheel_D.begin(); it != Wheel_D.end(); it++, i++)
	{
		int type = *it;
		if (type == 0)
			continue;
		switch (type)
		{
		case 2:	// �����[��
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

// �m�[�c����֐�
void CNotesMgr::NotesDecition()
{
	double timing = 0.0f;
	int i = 0, j = 0;
	int Up = SelectLane.front();
	int Down = SelectLane.back();
	// ---�m�[�c����---
	// ���m�[�}���m�[�c
	if (CInput::GetKeyboardData(DIK_Z, TRIGGER) || CInput::GetKeyboardData(DIK_X, TRIGGER))
	{
		timing = HIT_TIMING;
		int Quick = -1;// ��ԑ����m�[�c�̔ԍ�
		for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_L]; i++)
		{
			// �m�[�c�������Ă��邩
			if (!NormalLeftNotes[i]->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				// ��v���Ă���Δ�����
				if (NormalLeftNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			// ��v���������Ă���Ζ߂�
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
			if (fabs(NormalLeftNotes[i]->GetTiming()) < HIT_TIMING)
			{
				// ����ɓ����Ă�����̂̒��ň�ԋ߂���Βl�X�V
				if (fabs(NormalLeftNotes[i]->GetTiming()) < fabs(timing))
				{
					timing = NormalLeftNotes[i]->GetTiming();
					Quick = i;
				}
			}
		}
		if (Quick != -1)
		{
			// �m�[�c�G�t�F�N�g
			for (vector<CNotesEffect*>::iterator it2 = m_NotesEffect.begin(); it2 != m_NotesEffect.end(); it2++)
			{
				CNotesEffect* effect = *it2;
				if (effect->GetUseFlag())
					continue;
				effect->Create(NormalLeftNotes[Quick]->GetLaneNum());
				break;
			}
			// �m�[�c������������X�R�A���Z��Ȃ�₩���
			NormalScoreAdd(timing);
			NormalLeftNotes[Quick]->SetUseFlag(false);
			ComboAdd();
			CLane::getInstance()->NotesEffect(NormalLeftNotes[Quick]->GetLaneNum(), NormalLeftNotes[Quick]->GetLaneType());
		}
	}
	// ���m�[�}�������O�m�[�c
	if (CInput::GetKeyboardData(DIK_Z, PRESS) || CInput::GetKeyboardData(DIK_X, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = NormalLeftLongNotes.begin(); it != NormalLeftLongNotes.end(); it++)
		{
			// �m�[�c�������Ă��邩
			if (!(*it)->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				// ��v���Ă���Δ�����
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// ��v���������Ă���Ζ߂�
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// �X�R�A���Z��Ȃ�₩���
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// �m�[�c�G�t�F�N�g
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

	// �E�m�[�}���m�[�c
	if (CInput::GetKeyboardData(DIK_C, TRIGGER) || CInput::GetKeyboardData(DIK_V, TRIGGER))
	{
		int Quick = -1;// ��ԑ����m�[�c�̔ԍ�
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_NORMAL_R]; i++)
		{
			// �m�[�c�������Ă��邩
			if (!NormalRightNotes[i]->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				if (NormalRightNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
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
			// �m�[�c�G�t�F�N�g
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
	// �E�m�[�}�������O�m�[�c
	if (CInput::GetKeyboardData(DIK_C, PRESS) || CInput::GetKeyboardData(DIK_V, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = NormalRightLongNotes.begin(); it != NormalRightLongNotes.end(); it++)
		{
			// �m�[�c�������Ă��邩
			if (!(*it)->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				// ��v���Ă���Δ�����
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// ��v���������Ă���Ζ߂�
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// �X�R�A���Z��Ȃ�₩���
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// �m�[�c�G�t�F�N�g
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

	// ���N���b�N�m�[�c
	if (CInput::GetMouseData(Mouse_Data::L_BUTTON, TRIGGER))
	{
		int Quick = -1;// ��ԑ����m�[�c�̔ԍ�
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_CLICK_L]; i++)
		{
			// �m�[�c�������Ă��邩
			if (!ClickLeftNotes[i]->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				if (ClickLeftNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
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
			// �m�[�c�G�t�F�N�g
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
	// ���N���b�N�����O�m�[�c
	if (CInput::GetMouseData(Mouse_Data::L_BUTTON, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = ClickLeftLongNotes.begin(); it != ClickLeftLongNotes.end(); it++)
		{
			// �m�[�c�������Ă��邩
			if (!(*it)->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				// ��v���Ă���Δ�����
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// ��v���������Ă���Ζ߂�
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// �X�R�A���Z��Ȃ�₩���
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// �m�[�c�G�t�F�N�g
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

	// �E�N���b�N�m�[�c
	if (CInput::GetMouseData(Mouse_Data::R_BUTTON, TRIGGER))
	{
		int Quick = -1;// ��ԑ����m�[�c�̔ԍ�
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_CLICK_R]; i++)
		{
			// �m�[�c�������Ă��邩
			if (!ClickRightNotes[i]->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				if (ClickRightNotes[i]->GetLaneNum() == j)
				{
					break;
				}
			}
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
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
			// �m�[�c�G�t�F�N�g
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
	// �E�N���b�N�����O�m�[�c
	if (CInput::GetMouseData(Mouse_Data::R_BUTTON, PRESS))
	{
		for (vector<CLongNotes*>::iterator it = ClickRightLongNotes.begin(); it != ClickRightLongNotes.end(); it++)
		{
			// �m�[�c�������Ă��邩
			if (!(*it)->GetUseFlag())
				continue;
			// ���[������v���Ă��邩
			for (j = Up; j <= Down; j++)
			{
				// ��v���Ă���Δ�����
				if ((*it)->GetLaneNum() == j)
				{
					break;
				}
			}
			// ��v���������Ă���Ζ߂�
			if (j > Down)
				continue;

			// ����^�C�~���O�ɓ����Ă��邩
			if ((*it)->GetTiming() > -MajorBeatTime)
			{
				if ((*it)->GetDecitionFlag())
				{
					(*it)->SetDecitionFlag(false);
					// �X�R�A���Z��Ȃ�₩���
					Score += 1000;
					mPlayDataMgr->SetPlayData(eData_Score, Score);
					ComboAdd();
					CLane::getInstance()->NotesEffect((*it)->GetLaneNum(), (*it)->GetLaneType());
					// �m�[�c�G�t�F�N�g
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

	// ��z�C�[���m�[�c
	if (CInput::GetMouseWheel() > 0)
	{
		int Quick = -1;// ��ԑ����m�[�c�̔ԍ�
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_U]; i++)
		{
			// �m�[�c�������Ă��邩
			if (!WheelUpNotes[i]->GetUseFlag())
				continue;
			// ���[������v���Ă��邩

			// ����^�C�~���O�ɓ����Ă��邩
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
			// �m�[�c�G�t�F�N�g
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
	// ���z�C�[���m�[�c
	if (CInput::GetMouseWheel() < 0)
	{
		int Quick = -1;// ��ԑ����m�[�c�̔ԍ�
		double timing = HIT_TIMING;
		for (i = 0; i < NotesNum[NOTES_LIST_WHEEL_D]; i++)
		{
			// �m�[�c�������Ă��邩
			if (!WheelDownNotes[i]->GetUseFlag())
				continue;
			// ���[������v���Ă��邩


			// ����^�C�~���O�ɓ����Ă��邩
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
			// �m�[�c�G�t�F�N�g
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

// �X�R�A���Z�֐�
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
		{// �����I
			GreatQuickCount++;
			NotesDecision.Active(DECISION_FAST);
			//mPlayDataMgr->SetPlayData(, GreatQuickCount)
		}
		else
		{// �x���I
			GreatSlowCount++;
			NotesDecision.Active(DECISION_SLOW);
		}
	}
	else if (fabs(timing) < GOOD_TIMING)
	{
		NowCombo = 0;	// �R���{���������I
		Score += 300;
		if (timing < 0)
		{// �����I
			GoodQuickCount++;
			NotesDecision.Active(DECISION_FAST);
		}
		else
		{// �x���I
			GoodSlowCount++;
			NotesDecision.Active(DECISION_SLOW);
		}
	}
	else
	{
		MissCount++;
		NowCombo = 0;// �R���{��������
		Score += 100;
	}
	mPlayDataMgr->SetPlayData(eData_Score, Score);
}

// �R���{���Z�֐�
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

// �I�����[���X�V�֐�
void CNotesMgr::SetSelectLane(deque<int> selectLane)
{
	SelectLane.clear();
	SelectLane = selectLane;
}

// �y�ȏI���m�F�֐�
bool CNotesMgr::SoundEndCheck()
{
	return SoundEndFlag;
}