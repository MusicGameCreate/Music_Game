// ���f���`��e���v���[�g�N���X
// �h���N���X
#ifndef _CMODEL_TEMPLATE_H_
#define _CMODEL_TEMPLATE_H_

//********************************************************
//�C���N���[�h��
//********************************************************
#include "CModel_Base.h"

//********************************************************
//�N���X��`
//********************************************************
class Model_Template :public CModel_Base
{
private:

public:
	void		Update();				// �X�V
	void		Draw();					// �`��

	Model_Template();					// �R���X�g���N�^
	virtual ~Model_Template();			// �f�X�g���N�^
};

#endif