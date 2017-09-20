//***********************************************************************************************************
//
// ���U���g�V�[���N���X
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "Result_Scene.h"

//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
Result_Scene::Result_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr) : CBaseScene(changer)
{
	// �����ŃI�u�W�F�N�g��new����
	mPlayDataMgr = datamgr;

	Background		= new Result_Background;
	Frame			= new Result_Frame;
	NowScore		= new Result_NowScore( mPlayDataMgr->GetPlayData(eData_Score) );
	HiScore			= new Result_HiScore;
	Jacket			= new Result_Jacket;
	DifficultType	= new Result_DifficultType( 1 );
	DifficultLevel	= new Result_DifficultLevel(18);
	MaxComboNum		= new Result_MaxComboNum( mPlayDataMgr->GetPlayData( eData_NowCombo ) );
	BCWGauge		= new Result_BCWGauge;
	Circuit			= new Result_Circuit;
	TitleFont		= new Result_TitleFont(L"�����~�N�̏���", 7);	// ������A������
	ComposerName	= new Result_ComposerName(L"Cosmo@�\��P", 9);
	ClearGaugeNum	= new Result_ClearGaugeNum( 57 );



	ResultBGM = new CSound;
	ResultBGM->Init("../DATA/BGM/Main.wav");
	int playTime = ResultBGM->GetSoundFileLength();
	ResultBGM->SetCurrentPosition((float)playTime / 2.0f);
	ResultBGM->Play(true);
	double time = ResultBGM->GetNowPlayTime();
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
Result_Scene::~Result_Scene(void)
{
	// �����ŃI�u�W�F�N�g��delete����
	delete Background;
	delete Frame;
	delete NowScore;
	delete HiScore;
	delete Jacket;
	delete DifficultType;
	delete DifficultLevel;
	delete MaxComboNum;
	delete BCWGauge;
	delete Circuit;
	delete TitleFont;
	delete ComposerName;
	delete ClearGaugeNum;

	ResultBGM->Stop();
	delete ResultBGM;

}

void Result_Scene::Initialize()
{

}

void Result_Scene::Finalize()
{

}

//***********************************************************************************************************
// �X�V
//***********************************************************************************************************
void Result_Scene::Update(void)
{
	// �����ŃI�u�W�F�N�g��update����
	Background->Update();
	Frame->Update();
	NowScore->Update();
	HiScore->Update();
	Jacket->Update();
	DifficultType->Update();
	DifficultLevel->Update();
	MaxComboNum->Update();
	BCWGauge->Update();
	Circuit->Update();
	TitleFont->Update();
	ComposerName->Update();
	ClearGaugeNum->Update();

	if (CInput::GetKeyboardData(DIK_RETURN, TRIGGER))
	{
		mSceneChanger->ChangeScene(eScene_MusicSelect);
	}
}

//***********************************************************************************************************
// �`��
//***********************************************************************************************************
void Result_Scene::Draw(void)
{
	// �`�揇�͏�̍s���珇��(�A��2D�x�[�X�摜�͂��̌���ł͂���܂���)
	Background->Draw();		// �w�i�F
	Circuit->Draw();		// �w�i�E��H
	Frame->Draw();			// ���g
	NowScore->Draw();		// ���݃X�R�A
	HiScore->Draw();		// �ߋ��ō��X�R�A
	Jacket->Draw();			// �v���C�ȃW���P�b�g
	DifficultType->Draw();	// ��Փx����
	DifficultLevel->Draw();	// ��Փx���x��
	MaxComboNum->Draw();	// �ő�R���{��
	BCWGauge->Draw();		// �{�^���E�N���b�N�E�z�C�[���Q�[�W
	TitleFont->Draw();		// �ȃ^�C�g��
	ComposerName->Draw();	// ��ȎҖ�
	ClearGaugeNum->Draw();	// �N���A�Q�[�W����

}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************