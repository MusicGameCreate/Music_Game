//************************************************
// �C���N���[�h��
//************************************************
#include "Option_Back.h"

//************************************************
// �R���X�g���N�^
//************************************************
Option_Back::Option_Back()
{
	// �I�u�W�F�N�g�����������邩�H(�Œ� 1�`)
	nObject_Num = 1;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// ���W(�摜�̒��S�����_)
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		Tex_2D_Data[i].Obj_Size = D3DXVECTOR2(600, 500);

		// �e�N�X�`�����W(0.0f�`1.0f)
		Tex_2D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// �摜��RGBA�l
		Tex_2D_Data[i].Red =
		Tex_2D_Data[i].Green =
		Tex_2D_Data[i].Brue =
		Tex_2D_Data[i].Alpha = 255;

		// �摜�̊g�嗦(0.0f�`)
		Tex_2D_Data[i].fScale = 1.0f;

		// �摜�̉�]�p�x(0.0f�`)
		Tex_2D_Data[i].fRot = 0.0f;
	}


	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/Option.png", 0);
}

//************************************************
// �f�X�g���N�^
//************************************************
Option_Back::~Option_Back()
{
	CTexture_2D_Base::Finalise();
}

//************************************************
// void Option_Back::Update
// �����F�X�V����
// �����F�Ȃ��@�߂�l�F�Ȃ�
//************************************************
void Option_Back::Update()
{

	CTexture_2D_Base::Update();
}

//************************************************
// void Option_Back::Draw
// �����F�`�揈��
// �����F�Ȃ��@�߂�l�F�Ȃ�
//************************************************
void Option_Back::Draw()
{
	CTexture_2D_Base::Draw(0,0);
}