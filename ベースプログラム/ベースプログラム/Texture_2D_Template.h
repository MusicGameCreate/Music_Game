// 2D�摜�`��N���X
#ifndef _TEXTURE_2D_TEMPLATE_H_
#define _TEXTURE_2D_TEMPLATE_H_

//******************************************
// �C���N���[�h��
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// �N���X��`
//******************************************
class Texture_2D_Template : public CTexture_2D_Base
{
private:

public:
	void Update();					// �X�V
	void Draw();						// �`��

	Texture_2D_Template();			// �R���X�g���N�^
	virtual ~Texture_2D_Template();	// �f�X�g���N�^
};

#endif