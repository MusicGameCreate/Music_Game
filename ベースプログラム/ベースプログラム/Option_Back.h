#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class Option_Back : public CTexture_2D_Base
{
private:

public:
	void Update();				// �X�V
	void Draw();				// �`��

	Option_Back();				// �R���X�g���N�^
	virtual ~Option_Back();		// �f�X�g���N�^
};