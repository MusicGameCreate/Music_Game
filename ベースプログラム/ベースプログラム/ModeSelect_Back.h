#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class ModeSelect_Back : public CTexture_2D_Base
{
private:

public:
	void Update();				// �X�V
	void Draw();				// �`��

	ModeSelect_Back();			// �R���X�g���N�^
	virtual ~ModeSelect_Back();	// �f�X�g���N�^
};