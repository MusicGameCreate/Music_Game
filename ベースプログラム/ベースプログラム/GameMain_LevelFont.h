#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class GameMain_LevelFont : public CTexture_2D_Base
{
private:

public:
	void Update();					// �X�V
	void Draw();					// �`��

	GameMain_LevelFont();			// �R���X�g���N�^
	virtual ~GameMain_LevelFont();	// �f�X�g���N�^
};