//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "GameMain_MusicDataFrame.h"

//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
GameMain_MusicDataFrame::GameMain_MusicDataFrame()
{
	// �I�u�W�F�N�g�����������邩�H(�Œ� 1�`)
	//*******************************************************************************************************
	nObject_Num = 2;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//*******************************************************************************************************
	nUse_Texture_Num = 2;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// ���W(�摜�̒��S�����_)
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0.0f);

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		Tex_2D_Data[i].Obj_Size = D3DXVECTOR2(SCREEN_WIDTH, 160);

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

	Tex_2D_Data[1].Alpha = 0;
	nFrameCount = 0;
	nAddAlpha = 5;

	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/�ȏ��g_1.png", 0);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/�ȏ��g_2.png", 1);
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
GameMain_MusicDataFrame::~GameMain_MusicDataFrame()
{
	CTexture_2D_Base::Finalise();
}

//***********************************************************************************************************
// void GameMain_Back::Update
// �����F�X�V����
// �����F�Ȃ��@�߂�l�F�Ȃ�
//***********************************************************************************************************
void GameMain_MusicDataFrame::Update()
{
	Tex_2D_Data[1].Alpha += nAddAlpha;

	if (Tex_2D_Data[1].Alpha > 200 || Tex_2D_Data[1].Alpha <= 0)
	{
		nAddAlpha *= -1;
	}

	CTexture_2D_Base::Update();
}

//***********************************************************************************************************
// void GameMain_Back::Draw
// �����F�`�揈��
// �����F�Ȃ��@�߂�l�F�Ȃ�
//***********************************************************************************************************
void GameMain_MusicDataFrame::Draw()
{
	CTexture_2D_Base::Draw(0, 0);

	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CTexture_2D_Base::Draw(1, 1);
}