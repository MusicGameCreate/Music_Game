#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_3D_Base.h"

//******************************************
// �N���X��`
//******************************************
class Title_Bill : public CTexture_3D_Base
{
private:
	int nAddAlpha;

public:
	void Update();			// �X�V
	void Draw();			// �`��

	Title_Bill();			// �R���X�g���N�^
	virtual ~Title_Bill();	// �f�X�g���N�^
};