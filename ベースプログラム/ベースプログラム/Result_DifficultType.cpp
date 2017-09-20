//*************************************************************************
//
// ���U���g��ʁE��Փx����
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "Result_DifficultType.h" 
#include "Alphabet.h"
#include "DirectX_Library.h"

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
Result_DifficultType::Result_DifficultType(int nData)
{

	// ��Փx�̎�ނ��i�[
	//**********************************************************************
	nDifficult_Type = nData;

	{	// ��Փx�ʏ���
		if (nDifficult_Type == 0)
		{	// EASY����
			nObject_Num = 4;
			Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

			Tex_2D_Data[0].Tex_Pos = Get_Alphabet_Tex("E");
			Tex_2D_Data[1].Tex_Pos = Get_Alphabet_Tex("A");
			Tex_2D_Data[2].Tex_Pos = Get_Alphabet_Tex("S");
			Tex_2D_Data[3].Tex_Pos = Get_Alphabet_Tex("Y");
		}

		if (nDifficult_Type == 1)
		{	// HYPER����
			nObject_Num = 5;
			Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

			Tex_2D_Data[0].Tex_Pos = Get_Alphabet_Tex("H");
			Tex_2D_Data[1].Tex_Pos = Get_Alphabet_Tex("Y");
			Tex_2D_Data[2].Tex_Pos = Get_Alphabet_Tex("P");
			Tex_2D_Data[3].Tex_Pos = Get_Alphabet_Tex("E");
			Tex_2D_Data[4].Tex_Pos = Get_Alphabet_Tex("R");
		}

		if (nDifficult_Type == 2)
		{	// MASTER����
			nObject_Num = 6;
			Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

			Tex_2D_Data[0].Tex_Pos = Get_Alphabet_Tex("M");
			Tex_2D_Data[1].Tex_Pos = Get_Alphabet_Tex("A");
			Tex_2D_Data[2].Tex_Pos = Get_Alphabet_Tex("S");
			Tex_2D_Data[3].Tex_Pos = Get_Alphabet_Tex("T");
			Tex_2D_Data[4].Tex_Pos = Get_Alphabet_Tex("E");
			Tex_2D_Data[5].Tex_Pos = Get_Alphabet_Tex("R");
		}
	}

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = 2;

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	45.0f + 35.0f * i, 280.0f, 0.0f );

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 40.0f, 40.0f );

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( Get_Alphabet_Texture_Width(), Get_Alphabet_Texture_Height() );

		// �摜��RGBA�l
		//******************************************************************
		Tex_2D_Data[i].Red  =
		Tex_2D_Data[i].Green=
		Tex_2D_Data[i].Brue =
		Tex_2D_Data[i].Alpha= 255;

		// �摜�̊g�嗦( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// �摜�̉�]�p�x( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	CTexture_2D_Base::Init();

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/���ʎg�p/ALPHABET.png", 0 );

	// ��Փx�ʂɉ��H�摜�����[�h
	//**********************************************************************
	if (nDifficult_Type == 0)
		CREATE_TEXTURE( pTexture[1], 0xff55ff55 );
	if (nDifficult_Type == 1)
		CREATE_TEXTURE( pTexture[1], 0xffffff00 );
	if (nDifficult_Type == 2)
		CREATE_TEXTURE( pTexture[1], 0xffff3737 );
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
Result_DifficultType::~Result_DifficultType(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void Result_DifficultType::Update(void)
{

	CTexture_2D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
void Result_DifficultType::Draw(void)
{
	CTexture_2D_Base::Texture_Blend( 1,1, ADD );

	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_2D_Base::Draw(i, 0);
	}

	CTexture_2D_Base::Texture_Blend( 1, NULL, NULL );
}

//*************************************************************************
// EOF
//*************************************************************************
