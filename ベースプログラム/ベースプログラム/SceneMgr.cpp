//***********************************************************************************************************
//�@CScene_Base.cpp
//	�V�[���؂�ւ��N���X
//***********************************************************************************************************
#include "SceneMgr.h"
#include "Title_Scene.h"		// �^�C�g�����
#include "ModeSelect_Scene.h"	// ���[�h�Z���N�g���
#include "Option_Scene.h"		// �I�v�V�������
#include "MusicSelect_Scene.h"	// �ȃZ���N�g���
#include "GameMain_Scene.h"		// �Q�[�����C�����
#include "Result_Scene.h"		// ���U���g���

//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
CSceneMgr::CSceneMgr()
{
	mScene = (CBaseScene*)new MusicSelect_Scene(this, this);
	mScene->Initialize();
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
CSceneMgr::~CSceneMgr()
{

}

//***********************************************************************************************************
// void CScene_Base::Init
// �����F����������
// �����F�Ȃ��@�߂�l�F�Ȃ�
//***********************************************************************************************************
void CSceneMgr::Initialize()
{
}

void CSceneMgr::Finalize()
{
	mScene->Finalize();
}

//***********************************************************************************************************
// void CScene_Base::Update
// �����F���݃V�[�������� �X�V�A�`��A�I��������
// �����F�Ȃ��@�߂�l�F�Ȃ�
//***********************************************************************************************************
void CSceneMgr::Update()
{
	while (1)
	{
		if (mNextScene != eScene_None && mNextScene != eScene_End)
		{// ���̃V�[�����Z�b�g����Ă����
			mScene->Finalize();	// ���݂̃V�[���̏I�����������s
			delete mScene;
			switch (mNextScene)
			{
			case eScene_Title:
				mScene = (CBaseScene*) new Title_Scene(this);	// �^�C�g����ʂ̃C���X�^���X���쐬
				break;
			case eScene_ModeSelect:
				mScene = (CBaseScene*) new ModeSelect_Scene(this);
				break;
			case eScene_Option:
				mScene = (CBaseScene*) new Option_Scene(this);
				break;
			case eScene_MusicSelect:
				mScene = (CBaseScene*) new MusicSelect_Scene(this, this);
				break;
			case eScene_Game:
				mScene = (CBaseScene*) new GameMain_Scene(this, this);
				break;
			case eScene_Result:
				mScene = (CBaseScene*) new Result_Scene(this, this);
				break;
			};
			mNextScene = eScene_None;
			mScene->Initialize();
		}
		mScene->Update(); //���̃V�[���̍X�V
		if (mNextScene == eScene_None || mNextScene == eScene_End)
			break;
	}
}

// �`�揈��
void CSceneMgr::Draw(void)
{
	mScene->Draw();
}

// ���̃V�[����ݒ�
void CSceneMgr::ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;	// ���̃V�[�����Z�b�g
}

void CSceneMgr::SetPlayData(eDataType datatype, int nData)
{
	mPlayDataMgr.SetPlayData(datatype, nData);
}

int CSceneMgr::GetPlayData(eDataType datatype)
{
	return mPlayDataMgr.GetPlayData(datatype);
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************