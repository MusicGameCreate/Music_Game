//***********************************************************************************************************
//
// �ȃZ���N�g�V�[���ꊇ�Ǘ�
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS

#include "MusicSelect_Scene.h"
#include "CInput.h"
#include <locale.h>

//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
MusicSelect_Scene::MusicSelect_Scene(ISceneChanger* changer, IPlayDataMgr* dataMgr) : CBaseScene(changer)
{
	// �����ŃI�u�W�F�N�g��new����
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
	// �ȑ������T�C�Y�m��
	//*******************************************************************************************************
	M_Data = new MUSICSELECT_ALL_DATA[CMusic_Manager::Get_Music_Count()];
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
MusicSelect_Scene::~MusicSelect_Scene(void)
{
	// �����ŃI�u�W�F�N�g��delete����
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
	// �ȃZ���N�g��ʂɕK�v�ȏ���S�Ē��o
	//*******************************************************************************************************
	for (int i = 0; i < CMusic_Manager::Get_Music_Count(); i++)
	{
		// 1�񏑂����߂Ηǂ����ׂ̈Ɏg�p
		bool bWrite_Flg = false;

		// �C�[�W�[�E�n�C�p�[�E�}�X�^�[���ʓǂݍ���
		for (int j = 0; j < 3; j++)
		{
			// �e��Փx�ŕ��ʃf�[�^�������ꍇ�̓X�L�b�v
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

			// ���ʃf�[�^�ǂݍ���
			//*************************************************
			string FileName = CMusic_Manager::Get_MusicData(i)->Fumen_Path[j];
			Reader.JacketFileLoad(FileName);

			if (bWrite_Flg == false)
			{
				// �Ȗ�
				//*****************************************************
				M_Data[i].Music_Data.Jacket.TitleName = Reader.GetMusicData()->Jacket.TitleName;

				// BPM
				//*****************************************************
				M_Data[i].Music_Data.Jacket.Bpm = Reader.GetMusicData()->Jacket.Bpm;

				// ��ȎҖ�
				//*****************************************************
				M_Data[i].Music_Data.Jacket.ArtistName = Reader.GetMusicData()->Jacket.ArtistName;

				// �W���P�b�g�����
				//*****************************************************
				M_Data[i].Music_Data.Jacket.IllustratorName = Reader.GetMusicData()->Jacket.IllustratorName;

				// ���ʐ����
				//*****************************************************
				M_Data[i].Music_Data.Jacket.CreatorName = Reader.GetMusicData()->Jacket.CreatorName;

				// �ȃX�^�[�g�ʒu
				//*****************************************************
				M_Data[i].Music_Data.Jacket.Pst = Reader.GetMusicData()->Jacket.Pst;

				// �I�ȉ�ʂŗ��������̒���
				//*****************************************************
				M_Data[i].Music_Data.Jacket.Ple = Reader.GetMusicData()->Jacket.Ple;

				// 1�񏑂����񂾂̂Ńt���O�𗧂Ă�
				//*****************************************************
				bWrite_Flg = true;
			}

			// �e��Փx���x��
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

	// ���ݑI�𒆂̋ȃf�[�^��ݒ�
	//*******************************************************************************************************
	nSelect_Data = 3;

	// ���ݑI�𒆂̓�Փx��EASY�ɐݒ�
	//*******************************************************************************************************
	nNow_Difficult = EASY;

	// �㉺�ړ��t���O��������
	//*******************************************************************************************************
	bMove_Up = false;
	bMove_Down = false;

	// �t���[���J�E���g��������
	//*******************************************************************************************************
	nFrame_Count = 0;

	// �f�[�^�ύX�^�C�~���O��������
	//*******************************************************************************************************
	bData_Change_Flg = true;

	// locale.h���g�p���邽��
	//*******************************************************************************************************
	setlocale(LC_ALL, "jpn");
}

void MusicSelect_Scene::Finalize()
{

}

//***********************************************************************************************************
// �X�V
//***********************************************************************************************************
void MusicSelect_Scene::Update(void)
{
	
	//*********************************************************************
	// �L�[�{�[�h����
	//*********************************************************************
	// ���E���L�[�ňړ���ƁA���E���L�[�œ�Փx�Z���N�g
	//*********************************************************************
	{
		// ���L�[����
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

		// ���L�[����
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

		// ���L�[����
		if (CInput::GetKeyboardData(DIK_LEFT, TRIGGER))
		{
			switch (nNow_Difficult)
			{
			case EASY:   nNow_Difficult = EASY;  break;
			case HYPER:  nNow_Difficult = EASY;  break;
			case MASTER: nNow_Difficult = HYPER; break;
			}
		}

		// ���L�[����
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

	// �G���^�[�L�[�őI�𒆂̋ȏ���n���āA�Q�[�����C���ֈړ�
	if (CInput::GetKeyboardData(DIK_RETURN, TRIGGER))
	{
		// �I�����ꂽ�ȏ���n��
		mPlayDataMgr->SetPlayData(eData_SelectMusicNum, nSelect_Data);
		mPlayDataMgr->SetPlayData(eData_Difficult, nNow_Difficult);

		// �Q�[���V�[���ֈڍs
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
	{	// �I�ȃf�[�^�Ԓn���}�C�i�X�l�ɍs������ő�l-1 �ɏC��
		nSelect_Data = CMusic_Manager::Get_Music_Count() - 1;
	}

	if (nSelect_Data >= CMusic_Manager::Get_Music_Count())
	{	// �I�ȃf�[�^�Ԓn���ő�l�ɍs������0 �ɏC��
		nSelect_Data = 0;
	}

	// �����ŃI�u�W�F�N�g��update����
	BackGround->Update();								// �w�i
	BackEffect->Update();								// �w�i�G�t�F�N�g
	LeftFrame->Update();								// �����g
	BPM->Update(M_Data[nSelect_Data].Music_Data.Jacket.Bpm);	// BPM

	//*********************************************************************
	// string �� wchar_t�ɕϊ�
	//*********************************************************************
	wchar_t	wStrW[100];
	int		Len = 0;

	// �W���P�b�g����Җ��ϊ�
	//**********************************
	{	
		// string �� char* �ɕϊ�
		//**************************************************
		char* sz_Illustrator = new char[M_Data[nSelect_Data].Music_Data.Jacket.IllustratorName.size() + 1];
		std::strcpy(sz_Illustrator, M_Data[nSelect_Data].Music_Data.Jacket.IllustratorName.c_str());
		// char* �� wchar_t �ɕϊ�
		//**************************************************
		Len = mbstowcs(wStrW, sz_Illustrator, 100);

		delete[] sz_Illustrator;
	}

	// �W���P�b�g�����
	Illustrator->Update( wStrW, Len, bData_Change_Flg );		

	// ���ʐ���Җ��ϊ�
	//**********************************
	{	
		// string �� char* �ɕϊ�
		//**************************************************
		char* sz_CreatorName = new char[M_Data[nSelect_Data].Music_Data.Jacket.CreatorName.size() + 1];
		std::strcpy(sz_CreatorName, M_Data[nSelect_Data].Music_Data.Jacket.CreatorName.c_str());
		// char* �� wchar_t �ɕϊ�
		//**************************************************
		Len = mbstowcs(wStrW, sz_CreatorName, 100);

		delete[] sz_CreatorName;
	}

	// ���ʐ����
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

	Score->Update( nDisp_Score );			// �n�C�X�R�A

	bData_Change_Flg = false;
}

//***********************************************************************************************************
// �`��
//***********************************************************************************************************
void MusicSelect_Scene::Draw(void)
{
	// �`�揇�͏�̍s���珇��(�A��2D�x�[�X�摜�͂��̌���ł͂���܂���)
	BackGround->Draw();
	BackEffect->Draw();
	LeftFrame->Draw();
	BPM->Draw();
	Illustrator->Draw();
	Creator->Draw();

	// �E���܂Ƃ�
	for ( int i = 0 ; i < 7 ; i ++ )
	{
		// �t���[���`��
		int nJacketWork = RightFrame->Draw(i);


		// �W���P�b�g�`��
		Jacket->Draw(nJacketWork);

		// �e��Փx���x���`��
		Level->Draw(nJacketWork);
	}

	Score->Draw();
}