#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class Title_Back : public CTexture_2D_Base
{
private:

public:
	void Update();			// �X�V
	void Draw();			// �`��

	Title_Back();			// �R���X�g���N�^
	virtual ~Title_Back();	// �f�X�g���N�^
};