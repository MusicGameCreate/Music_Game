#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class Stage_Back : public CTexture_2D_Base
{
private:

public:
	void Update();			// �X�V
	void Draw();			// �`��

	Stage_Back();			// �R���X�g���N�^
	virtual ~Stage_Back();	// �f�X�g���N�^
};