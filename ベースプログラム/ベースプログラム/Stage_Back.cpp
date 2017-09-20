//************************************************
//�C���N���[�h��
//************************************************
#include "Stage_Back.h"

//************************************************
// �R���X�g���N�^
//************************************************
Stage_Back::Stage_Back()
{
	// �I�u�W�F�N�g�����g�p���邩�H(�Œ� 1�`)
	nObj_Num = 1;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	Tex_2D_Data = new TEXTURE_2D_DATA[nObj_Num];
	aVertex = new VERTEX_2D[NUM_VERTEX * nObj_Num];

	for (int i = 0; i < nObj_Num; i++)
	{
		// ���W(�摜�̒��S�����_)
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		Tex_2D_Data[i].Obj_Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

		// �e�N�X�`�����W(0.0f�`1.0f)
		Tex_2D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// �摜��RGBA�l
		Tex_2D_Data[i].Red = 255;
		Tex_2D_Data[i].Green = 255;
		Tex_2D_Data[i].Brue = 255;
		Tex_2D_Data[i].Alpha = 255;

		// �摜�̊g�嗦(0.0f�`)
		Tex_2D_Data[i].fScale = 1.0f;

		// �摜�̉�]�p�x(0.0f�`)
		Tex_2D_Data[i].fRot = 0.0f;
	}

	CTexture_2D_Base::Init("../DATA/TEXTURE/Title.png");
}

//************************************************
// �f�X�g���N�^
//************************************************
Stage_Back::~Stage_Back()
{
	CTexture_2D_Base::Finalise();
}

//************************************************
// void Stage_Back::Update
// �����F�X�V����
// �����F�Ȃ��@�߂�l�F�Ȃ�
//************************************************
void Stage_Back::Update()
{

	CTexture_2D_Base::Update();
}

//************************************************
// void Stage_Back::Draw
// �����F�`�揈��
// �����F�Ȃ��@�߂�l�F�Ȃ�
//************************************************
void Stage_Back::Draw()
{
	CTexture_2D_Base::Draw();
}