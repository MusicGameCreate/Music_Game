// ISceneChanger.h

#pragma once

typedef enum
{
	eScene_None,		// �Ȃ�
	eScene_Title,		// �^�C�g�����
	eScene_ModeSelect,	// ���[�h�Z���N�g
	eScene_Option,		// �I�v�V����
	eScene_MusicSelect,	// �ȃZ���N�g
	eScene_Game,		// �Q�[�����
	eScene_Result,		// ���U���g���
	eScene_End,			// �I��
}eScene;

// �V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger
{
public:
	virtual ~ISceneChanger(void) = 0;
	virtual void ChangeScene(eScene NextScene) = 0;	// �w��V�[���ɑJ��
};