//***********************************************************************************************************
//
// �S�V�[���ꊇ�Ǘ�
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
//#include "Title_Scene.h"		// �^�C�g�����
//#include "ModeSelect_Scene.h"	// ���[�h�Z���N�g���
//#include "Option_Scene.h"		// �I�v�V�������
//#include "MusicSelect_Scene.h"	// �ȃZ���N�g���
//#include "GameMain_Scene.h"		// �Q�[�����C�����
//#include "Result_Scene.h"		// ���U���g���
//#include "Fade_Scene.h"			// �t�F�[�h���
//#include "Load_Scene.h"			// ���[�h���
#include "BaseScene.h"
#include "PlayDataMgr.h"

//#include "CTimer.h"
//#include "CInput.h"

//***********************************************************************************************************
// �N���X��`
//***********************************************************************************************************
class CSceneMgr : public ISceneChanger, IPlayDataMgr
{
private:
	//Title_Scene*		Title_;			// �^�C�g���V�[���ꊇ�Ǘ�
	//ModeSelect_Scene*	ModeSelect_;	// ���[�h�Z���N�g�V�[���ꊇ�Ǘ�
	//Option_Scene*		Option_;		// �I�v�V�����V�[���ꊇ�Ǘ�
	//MusicSelect_Scene*	MusicSelect_;	// �ȃZ���N�g�V�[���ꊇ�Ǘ�
	//GameMain_Scene*		GameMain_;		// �Q�[�����C���V�[���ꊇ�Ǘ�
	//Result_Scene*		Result_;		// ���U���g�V�[���ꊇ�Ǘ�
	//Fade_Scene*			Fade_;			// �t�F�[�h�V�[���ꊇ�Ǘ�
	//Load_Scene*			Load_;			// ���[�h�V�[���ꊇ�Ǘ�
	
	//double				Timer;

	CBaseScene*			mScene;			// ���݂̃V�[��
	eScene				mNextScene;		// �ύX��̃V�[��
	PlayDataMgr			mPlayDataMgr;	// �f�[�^�Ǘ�
public:

	CSceneMgr(void);
	~CSceneMgr(void) override;
	void Initialize(void);
	void Finalize(void);
	void Update(void);
	void Draw(void);

	void SetPlayData(eDataType datatype, int nData)override;
	int GetPlayData(eDataType datatype) override;
	void ChangeScene(eScene NextScene) override;
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************