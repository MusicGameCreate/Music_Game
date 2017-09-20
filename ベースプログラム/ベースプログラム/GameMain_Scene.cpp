//***********************************************************************************************************
//
// �Q�[�����C���V�[���ꊇ�Ǘ�
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "GameMain_Scene.h"
//#include <boost/thread.hpp>

//using namespace boost;

//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
GameMain_Scene::GameMain_Scene(ISceneChanger* changer, IPlayDataMgr* datamgr) : CBaseScene(changer)
{
	mPlayDataMgr = datamgr;
	//thread InitThread(bind(&GameMain_Scene::Initialize, this));

	//InitThread.join();

	ShowCursor(FALSE);
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
GameMain_Scene::~GameMain_Scene(void)
{
	// �����ŃI�u�W�F�N�g��delete����
	delete Background;
	delete Score;
	delete ScoreFont;
	delete Music_Frame;
	delete Music_FrameBack;
	delete HoiruButton;
	delete Level;
	delete LevelFont;
	delete BPMFont;
	delete BPM;
	delete PushEffect;
	delete MaxCombo;
	delete MaxComboFont;
	delete JacketImage;
	delete Bar;
	delete HiSpeed;
	delete TimeServer;

	//delete Yuka;
	//delete Lane;
	delete NotesMgr;

	ShowCursor(TRUE);
}

void GameMain_Scene::Initialize()
{
	reader.JacketFileLoad("../DATA/MUSIC/LemonadeParty.music/lemon_E.score");
	// �����ŃI�u�W�F�N�g��new����
	Background = new GameMain_Background;		//
	Score = new GameMain_Score;			//
	ScoreFont = new GameMain_ScoreFont;		//
	Music_Frame = new GameMain_MusicDataFrame;
	Music_FrameBack = new GameMain_MusicFrameBack;
	HoiruButton = new GameMain_HoiruButton;
	Level = new GameMain_Level(reader.GetMusicData()->Jacket.Level);
	LevelFont = new GameMain_LevelFont;
	BPMFont = new GameMain_BPMFont;
	BPM = new GameMain_BPM(reader.GetMusicData()->Jacket.Bpm);
	PushEffect = new GameMain_PushEffect;

	MaxCombo = new GameMain_MaxCombo;
	MaxComboFont = new GameMain_MaxComboFont;
	JacketImage = new GameMain_JacketImage;
	Bar = new GameMain_Bar;
	HiSpeed = new GameMain_HiSpeed;

	//Yuka = new Model_Template;
	Lane = CLane::getInstance();
	NotesMgr = new CNotesMgr(mPlayDataMgr);
	TimeServer = new CTimeServer;
	NotesMgr->SetLaneData(Lane->GetLaneData());
	//NotesMgr->SetDataMgr(mPlayDataMgr);
	Bar->Initialize(Lane->GetLaneData().m_fLaneSize, PushEffect->GetSize().y);

	//NotesMgr->Initialize();
	//thread threadB(bind(&CNotesMgr::SoundPlay, NotesMgr));
	//thread threadA(bind(&CNotesMgr::Initialize, NotesMgr));
	NotesMgr->Initialize();

	//threadB.join();
	//threadA.join();
}

void GameMain_Scene::Finalize()
{

}

//***********************************************************************************************************
// �X�V
//***********************************************************************************************************
void GameMain_Scene::Update(void)
{
	CDirectX::Get_pD3DDevice()->ShowCursor(FALSE);
	// �����ŃI�u�W�F�N�g��update����
	TimeServer->Update();
	Background->Update();
	Music_Frame->Update();
	Music_FrameBack->Update();
	HoiruButton->Update();
	JacketImage->Update();
	Bar->Update();
	HiSpeed->Update();

	//Yuka->Update();
	Lane->SetSelectLane(Bar->GetSelectLane());
	Lane->Update();

	NotesMgr->SetSelectLane(Bar->GetSelectLane());
	NotesMgr->Update();

	// UI
	Score->SetScore(mPlayDataMgr->GetPlayData(eData_Score));
	Score->Update();
	ScoreFont->Update();
	Level->Update();
	LevelFont->Update();
	BPMFont->Update();
	BPM->Update();
	PushEffect->Update();
	MaxCombo->SetCombo(mPlayDataMgr->GetPlayData(eData_MaxCombo));
	MaxCombo->Update();
	MaxComboFont->Update();

	// �ȍĐ��I����
	if (NotesMgr->SoundEndCheck())
	{
		mSceneChanger->ChangeScene(eScene_Result);
	}
}

//***********************************************************************************************************
// �`��
//***********************************************************************************************************
void GameMain_Scene::Draw(void)
{
	// �`�揇�͏�̍s���珇��(�A��2D�x�[�X�摜�͂��̌���ł͂���܂���)
	Background->Draw();			// �w�i�F

	Music_FrameBack->Draw();	// �ȏ��E�g�w�i�F
	Music_Frame->Draw();		// �ȏ��E�g
	JacketImage->Draw();		// �ȏ��E�W���P�b�g
	Score->Draw();				// �X�R�A����
	ScoreFont->Draw();			// �X�R�A����
	MaxCombo->Draw();			// �R���{����
	MaxComboFont->Draw();		// �R���{����
	Level->Draw();				// ���x������
	LevelFont->Draw();			// ���x������
	BPM->Draw();				// BPM����
	BPMFont->Draw();			// BPM����

	HoiruButton->Draw();		// �㉺�z�C�[���{�^�������ʒu
	Bar->Draw();				// ����o�[

	PushEffect->Draw();			// �G�t�F�N�g
	HiSpeed->Draw();			// �E���n�C�X�s

								//Yuka->Draw();				// �����f��(�f�o�b�O�E�J�����m�F�p)
	Lane->Draw();
	NotesMgr->Draw();
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************