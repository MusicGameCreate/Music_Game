#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class Fade_Background : public CTexture_2D_Base
{
private:
	int		nAddAlpha;
	int		nFrameCnt;
	bool		bFrame;

public:
	void		Update();				// �X�V
	void		Draw();					// �`��

	Fade_Background();				// �R���X�g���N�^
	virtual ~Fade_Background();		// �f�X�g���N�^
};