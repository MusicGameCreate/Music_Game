//*************************************************************************
//
// �����ɃI�u�W�F�N�g�̐���
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "GameMain_HiSpeed.h" 
#include <math.h>

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
GameMain_HiSpeed::GameMain_HiSpeed(void)
{
	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num	= 4;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = 3;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	0.0f, 0.0f, 0.0f );

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 0.0f, 0.0f );

		// �e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

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

	Tex_2D_Data[0].Obj_Pos = D3DXVECTOR3(880.0f, 605.0f + 100.0f, 0.0f);
	Tex_2D_Data[0].Obj_Size = D3DXVECTOR2( 68.0f, 30.0f );


	Tex_2D_Data[1].Obj_Pos = D3DXVECTOR3(950.0f, 600.0f + 100.0f, 0.0f);
	Tex_2D_Data[1].Obj_Size = Tex_2D_Data[3].Obj_Size = D3DXVECTOR2(90.0f, 45.0f);
	Tex_2D_Data[1].Tex_Anim.x = Tex_2D_Data[3].Tex_Anim.x = 0.1f;

	Tex_2D_Data[2].Obj_Pos = D3DXVECTOR3(993.0f, 615.0f + 100.0f, 0.0f);
	Tex_2D_Data[2].Obj_Size = D3DXVECTOR2(20.0f, 15.0f);

	Tex_2D_Data[3].Obj_Pos = D3DXVECTOR3(1050.0f, 600.0f + 100.0f, 0.0f);

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/cross.png", 0);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/dot.png", 1);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/���ʎg�p/NUMBER.png", 2);

	fNow_Speed = 2.5f;
	nAdd_Speed = 0;
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
GameMain_HiSpeed::~GameMain_HiSpeed(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void GameMain_HiSpeed::Update(void)
{
	if (CInput::GetKeyboardData(DIK_RSHIFT, PRESS))
	{	// �E�V�t�g�������͎w��ʒu�܂ňړ�
		nAdd_Speed = -5;

		if (Tex_2D_Data[0].Obj_Pos.y <= 605.0f)
		{
			nAdd_Speed = 0;
		}

		// �E�V�t�g�������Ȃ��獶�E�L�[�Ńn�C�X�s�̑���
		if (CInput::GetKeyboardData(DIK_LEFT, TRIGGER))
		{	// ��
			fNow_Speed -= 0.100f;
		}
		if (CInput::GetKeyboardData(DIK_RIGHT, TRIGGER))
		{	// ��
			fNow_Speed += 0.100f;
		}

		// �����ݒ�
		if ( fNow_Speed <= 1.000f )
		{
			fNow_Speed = 1.000f;
		}
		// ����ݒ�
		if ( fNow_Speed >= 7.000f )
		{
			fNow_Speed = 7.000f;
		}

	}

	if (CInput::GetKeyboardData(DIK_RSHIFT, RELEASE))
	{	// �E�V�t�g�������u�Ԃɉ�ʊO��
		nAdd_Speed = 5;
	}

	if (Tex_2D_Data[0].Obj_Pos.y >= 710.0f)
	{
		Tex_2D_Data[0].Obj_Pos.y = 705.0f;
		Tex_2D_Data[1].Obj_Pos.y = 700.0f;
		Tex_2D_Data[2].Obj_Pos.y = 715.0f;
		Tex_2D_Data[3].Obj_Pos.y = 700.0f;
		nAdd_Speed = 0;
	}

	// �ړ�����
	for (int i = 0; i < nObject_Num; i++)
	{
		Tex_2D_Data[i].Obj_Pos.y += nAdd_Speed;
	}

	int nNum;

	// �����̃e�N�X�`���Z�b�g
	nNum = (int)(fNow_Speed / 1);
	Tex_2D_Data[1].Tex_Pos.x = (float)nNum * 0.100f;

	// �E���̃e�N�X�`���Z�b�g
	nNum = (int)( fNow_Speed * 10.000f );
	nNum = nNum % 10 / 1;
	Tex_2D_Data[3].Tex_Pos.x = (float)nNum * 0.100f;

	CTexture_2D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
void GameMain_HiSpeed::Draw(void)
{
	CTexture_2D_Base::Draw(0, 0);	// X
	CTexture_2D_Base::Draw(1, 2);	// ��
	CTexture_2D_Base::Draw(2, 1);	// .
	CTexture_2D_Base::Draw(3, 2);	// ��
}

//*************************************************************************
// EOF
//*************************************************************************
