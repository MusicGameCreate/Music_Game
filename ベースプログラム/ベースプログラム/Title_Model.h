#pragma once

//******************************************
// �C���N���[�h��
//******************************************
#include "CModel_Base.h"

//******************************************
// �N���X��`
//******************************************
class Title_Model : public CModel_Base
{
private:

public:
	void Update();			// �X�V
	void Draw();			// �`��

	Title_Model();			// �R���X�g���N�^
	virtual ~Title_Model();	// �f�X�g���N�^
};