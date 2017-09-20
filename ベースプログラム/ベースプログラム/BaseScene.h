// BaseScene.h

#pragma once

#include "ISceneChanger.h"

// �V�[���̊��N���X
class CBaseScene
{
protected:
	ISceneChanger*	mSceneChanger;	// �N���X���L���ɃV�[���؂�ւ���`����

public:
	CBaseScene(ISceneChanger* changer);

	virtual ~CBaseScene(void){}
	virtual void Initialize(void) {}	// �����������͎������Ȃ��Ă�����
	virtual void Finalize(void) {}		// �I�������͎������Ȃ��Ă�����
	virtual void Update(void) = 0;		// �X�V�����͕K���p����Ŏ���
	virtual void Draw(void) = 0;		// �`�揈���͕K���p����Ŏ���
};