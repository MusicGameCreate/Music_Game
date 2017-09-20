//*************************************************************************
//
// �����ɃI�u�W�F�N�g�̐���
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "MusicSelect_RightFrame.h" 

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
MusicSelect_RightFrame::MusicSelect_RightFrame(void)
{
	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num	= 7;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3( 770.0f, 365.0f, 0.0f );

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 700.0f, 230.0f);

		// �e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

		// �摜��RGBA�l
		//******************************************************************
		Tex_2D_Data[i].Red		=
		Tex_2D_Data[i].Green	=
		Tex_2D_Data[i].Brue		=
		Tex_2D_Data[i].Alpha	= 255;

		// �摜�̊g�嗦( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fScale	= 1.0f;

		// �摜�̉�]�p�x( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fRot		= 0.0f;

		// �ړ��������Z�b�g
		//******************************************************************
		Move_Vec[i].nMove_Vec_Up	= NULL;
		Move_Vec[i].nMove_Vec_Down	= NULL;
	}

	// �I�u�W�F�N�g�̏����ʒu�w��
	//**********************************************************************
	{
		// ��X�y�A
		Tex_2D_Data[0].Obj_Pos = POSITION_CENTER_UP_SPEAR;
		// 2�E��
		Tex_2D_Data[1].Obj_Pos = POSITION_CENTER_UP_UP;
		// 1�E��
		Tex_2D_Data[2].Obj_Pos = POSITION_CENTER_UP;
		// ���S
		Tex_2D_Data[3].Obj_Pos = POSITION_CENTER;
		// �P�E��
		Tex_2D_Data[4].Obj_Pos = POSITION_CENTER_DOWN;
		// 2�E��
		Tex_2D_Data[5].Obj_Pos = POSITION_CENTER_DOWN_DOWN;
		// ���X�y�A
		Tex_2D_Data[6].Obj_Pos = POSITION_CENTER_DOWN_SPEAR;
	}

	// �ړ��������w��
	//**********************************************************************
	{
		// ��X�y�A
		//**************************************
		Move_Vec[0].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[0].nMove_Vec_Down	= LEFT_DOWN;
		Move_Vec[0].nDraw_Order		= 0;

		// �Q�E��
		//**************************************
		Move_Vec[1].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[1].nMove_Vec_Down	= LEFT_DOWN;
		Move_Vec[1].nDraw_Order		= 1;

		// �P�E��
		//**************************************
		Move_Vec[2].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[2].nMove_Vec_Down	= LEFT_DOWN;
		Move_Vec[2].nDraw_Order		= 2;

		// ���S
		//**************************************
		Move_Vec[3].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[3].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[3].nDraw_Order		= 6;

		// �P�E��
		//**************************************
		Move_Vec[4].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[4].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[4].nDraw_Order		= 5;

		// �Q�E��
		//**************************************
		Move_Vec[5].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[5].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[5].nDraw_Order		= 4;

		// ���X�y�A
		//**************************************
		Move_Vec[6].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[6].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[6].nDraw_Order		= 3;

	}

	CTexture_2D_Base::Init();

	// �e�N�X�`���ǂݍ���
	//**********************************************************************
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/MusicSelect/�E�ȏ��g.png", 0 );
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
MusicSelect_RightFrame::~MusicSelect_RightFrame(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void MusicSelect_RightFrame::Update(int DIFFICULT, bool UP, bool DOWN)
{
	// �S�̏�ړ�
	//*********************************************************************
	if ( UP )
	{
		//*****************************************************************
		// �ړ�����
		//*****************************************************************
		for (int i = 0; i < nObject_Num; i++)
		{
			switch (Move_Vec[i].nMove_Vec_Up)
			{
			case LEFT_UP:
				Tex_2D_Data[i].Obj_Pos.x -= MOVE_POSITION.x / 10;
				Tex_2D_Data[i].Obj_Pos.y -= MOVE_POSITION.y / 10;
				break;

			case RIGHT_UP:
				Tex_2D_Data[i].Obj_Pos.x += MOVE_POSITION.x / 10;
				Tex_2D_Data[i].Obj_Pos.y -= MOVE_POSITION.y / 10;
				break;

			default:
				break;
			}
		}
	}// --- if ( UP )

	 // �S�̉��ړ�
	 //*********************************************************************
	if ( DOWN )
	{
		//*****************************************************************
		// �ړ�����
		//*****************************************************************
		for (int i = 0; i < nObject_Num; i++)
		{

			switch (Move_Vec[i].nMove_Vec_Down)
			{
			case LEFT_DOWN:
				Tex_2D_Data[i].Obj_Pos.x -= MOVE_POSITION.x / 10;
				Tex_2D_Data[i].Obj_Pos.y += MOVE_POSITION.y / 10;

				break;

			case RIGHT_DOWN:
				Tex_2D_Data[i].Obj_Pos.x += MOVE_POSITION.x / 10;
				Tex_2D_Data[i].Obj_Pos.y += MOVE_POSITION.y / 10;

				break;

			default:
				break;
			}
		}
	}// --- if ( DOWN )


	 // �ŉ��ɍs������ŏ�Ɉړ�
	 //*********************************************************************
	for (int i = 0; i < nObject_Num; i++)
	{
		if ( Tex_2D_Data[i].Obj_Pos.x <= RIMIT_POSITION_DOWN.x + 10.0f &&
			 Tex_2D_Data[i].Obj_Pos.x >= RIMIT_POSITION_DOWN.x - 10.0f &&
			 Tex_2D_Data[i].Obj_Pos.y >= RIMIT_POSITION_DOWN.y - 10.0f &&
			 Tex_2D_Data[i].Obj_Pos.y <= RIMIT_POSITION_DOWN.y + 10.0f )
		{
			Tex_2D_Data[i].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
			Move_Vec[i].nMove_Vec_Up	= RIGHT_UP;
			Move_Vec[i].nMove_Vec_Down	= LEFT_DOWN;
			Move_Vec[i].nDraw_Order		= 0;
		}
	}


	// �ŏ�ɍs������ŉ��Ɉړ�
	//*********************************************************************
	for (int i = 0; i < nObject_Num; i++)
	{
		if ( Tex_2D_Data[i].Obj_Pos.x <= RIMIT_POSITION_UP.x + 10.0f &&
			 Tex_2D_Data[i].Obj_Pos.x >= RIMIT_POSITION_UP.x - 10.0f &&
			 Tex_2D_Data[i].Obj_Pos.y >= RIMIT_POSITION_UP.y - 10.0f &&
			 Tex_2D_Data[i].Obj_Pos.y <= RIMIT_POSITION_UP.y + 10.0f )
		{
			Tex_2D_Data[i].Obj_Pos		= POSITION_CENTER_DOWN_SPEAR;
			Move_Vec[i].nMove_Vec_Up	= LEFT_UP;
			Move_Vec[i].nMove_Vec_Down	= RIGHT_DOWN;
			Move_Vec[i].nDraw_Order		= 3;
		}
	}

	if (!UP || !DOWN)
	{
		for (int i = 0; i < nObject_Num; i++)
		{
			Set_Move_Vec( Tex_2D_Data[i].Obj_Pos , i);
		}
	}

	// ��Փx�ɍ��킹�Ęg�̐F��ύX
	//*********************************************************************
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		switch ( DIFFICULT )
		{
		case EASY:  Tex_2D_Data[i].Red = 100; Tex_2D_Data[i].Green = 255; Tex_2D_Data[i].Brue = 150; break;
		case HYPER: Tex_2D_Data[i].Red = 255; Tex_2D_Data[i].Green = 255; Tex_2D_Data[i].Brue = 100; break;
		case MASTER:Tex_2D_Data[i].Red = 255; Tex_2D_Data[i].Green = 100; Tex_2D_Data[i].Brue = 100; break;
		}
	}


	CTexture_2D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
int MusicSelect_RightFrame::Draw(int NUMBER)
{
	int i = 0;

	while (1)
	{
		if (Move_Vec[i].nDraw_Order == NUMBER)
		{
			CTexture_2D_Base::Draw(i, 0);

			return i;
		}

		i++;
	}
}

//*************************************************************************
// �ړ��������Z�b�g
//*************************************************************************
void MusicSelect_RightFrame::Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum)
{
	D3DXVECTOR3 POS[7];

	POS[0] = POSITION_CENTER;
	POS[1] = POSITION_CENTER_UP;
	POS[2] = POSITION_CENTER_UP_UP;
	POS[3] = POSITION_CENTER_UP_SPEAR;
	POS[4] = POSITION_CENTER_DOWN;
	POS[5] = POSITION_CENTER_DOWN_DOWN;
	POS[6] = POSITION_CENTER_DOWN_SPEAR;

	for (int i = 0; i < nObject_Num; i++)
	{
		if (POSITION.x <= POS[i].x + 10.0f &&
			POSITION.x >= POS[i].x - 10.0f &&
			POSITION.y >= POS[i].y - 10.0f &&
			POSITION.y <= POS[i].y + 10.0f)
		{
			switch (i)
			{
			case 0:	// �Z���^�[
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 6;

				break;

			case 1:	// 1�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 2;

				break;

			case 2:	// 2�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 1;

				break;

			case 3:	// ��X�y�A
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 0;

				break;

			case 4:	// 1�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 5;

				break;

			case 5:	// 2�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 4;

				break;

			case 6:	// ���X�y�A
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN_SPEAR;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 3;

				break;

			default:
				break;
			}

			break;
		}
	}
}

//*************************************************************************
// EOF
//*************************************************************************
