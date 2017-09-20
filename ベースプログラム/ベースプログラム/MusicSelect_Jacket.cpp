//*************************************************************************
//
// �ȃZ���N�g��ʁE�W���P�b�g
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "MusicSelect_Jacket.h" 
#include "CMusic_Manager.h"

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
MusicSelect_Jacket::MusicSelect_Jacket(void)
{
	// �ȃf�[�^�̑������擾
	//**********************************************************************
	nAll_Music_Num = CMusic_Manager::Get_Music_Count();


	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num	= 7;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = nAll_Music_Num;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	// �ȑ������T�C�Y�m��
	//**********************************************************************
	Jacket_Data = new JACKET_DATA[nAll_Music_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	0.0f, 0.0f, 0.0f );

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 160.0f, 160.0f );

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

		// �ړ��������Z�b�g
		//******************************************************************
		Move_Vec[i].nMove_Vec_Up	= NULL;
		Move_Vec[i].nMove_Vec_Down	= NULL;

		// ���݂��ꂼ��̃I�u�W�F�N�g�ɃZ�b�g����Ă���e�N�X�`���ԍ����i�[
		//******************************************************************
		nNow_SetTexture[i] = i;

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

		// �Q�E��
		//**************************************
		Move_Vec[1].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[1].nMove_Vec_Down	= LEFT_DOWN;

		// �P�E��
		//**************************************
		Move_Vec[2].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[2].nMove_Vec_Down	= LEFT_DOWN;

		// ���S
		//**************************************
		Move_Vec[3].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[3].nMove_Vec_Down	= RIGHT_DOWN;

		// �P�E��
		//**************************************
		Move_Vec[4].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[4].nMove_Vec_Down	= RIGHT_DOWN;

		// �Q�E��
		//**************************************
		Move_Vec[5].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[5].nMove_Vec_Down	= RIGHT_DOWN;

		// ���X�y�A
		//**************************************
		Move_Vec[6].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[6].nMove_Vec_Down	= RIGHT_DOWN;

	}


	CTexture_2D_Base::Init();


	// �S�Ȃ̃W���P�b�g�摜�̓ǂݍ���
	//**********************************************************************
	for (int i = 0; i < nAll_Music_Num; i++)
	{
		if ( CMusic_Manager::Get_MusicData(i)->Jacket_In == false )
		{
			// �W���P�b�g�摜�������Ă��Ȃ��ꍇ�͉��̉摜�ɍ����ւ�
			//******************************************************************
			CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/���ʎg�p/JACKET_ERROR.png", i);
		}
		else
		{
			// �Ȃ̃W���P�b�g�̃p�X���擾
			//******************************************************************
			Jacket_Data[i].Music_Jacket_Pass = CMusic_Manager::Get_MusicData(i)->Picture_Path;

			// �擾�����W���P�b�g�̃p�X�Ńe�N�X�`���ǂݍ���
			//******************************************************************
			CTexture_2D_Base::Load_Texture(Jacket_Data[i].Music_Jacket_Pass, i);
		}

		// �e�N�X�`���ԍ����i�[
		//******************************************************************
		Jacket_Data[i].nTexture_Num = i;
	}
	
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
MusicSelect_Jacket::~MusicSelect_Jacket(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void MusicSelect_Jacket::Update(bool UP, bool DOWN)
{
	// �e�N�X�`��������W
	D3DXVECTOR2 T1 = D3DXVECTOR2( ( 0.0f + 0.5f ) / 160.0f , 
								  ( 0.0f + 0.5f ) / 160.0f );

	D3DXVECTOR2 T2 = D3DXVECTOR2( ( 0.0f + 160.0f + 0.5f ) / 160.0f , 
								  ( 0.0f + 160.0f + 0.5f ) / 160.0f );

	for (int i = 0; i < nObject_Num; i++)
	{
		Tex_2D_Data[i].Tex_Pos  = T1;
		Tex_2D_Data[i].Tex_Anim = T2;
	}

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

	if ( !bMove_Down || !bMove_Up )
	{
		for (int i = 0; i < nObject_Num; i++)
		{
			// �ŉ��ɍs������ŏ�Ɉړ� + �W���P�b�g�����̂֍X�V
			//*********************************************************************
			if (Tex_2D_Data[i].Obj_Pos.x <= RIMIT_POSITION_DOWN.x + 10.0f &&
				Tex_2D_Data[i].Obj_Pos.x >= RIMIT_POSITION_DOWN.x - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y >= RIMIT_POSITION_DOWN.y - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y <= RIMIT_POSITION_DOWN.y + 10.0f)
			{
				Tex_2D_Data[i].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
				Move_Vec[i].nMove_Vec_Up	= RIGHT_UP;
				Move_Vec[i].nMove_Vec_Down	= LEFT_DOWN;

				// �e�N�X�`���ԍ��ύX
				//*****************************************************************
				int nWork = i - 6;

				switch (nWork)
				{
				case -1: nWork = 6; break;
				case -2: nWork = 5; break;
				case -3: nWork = 4; break;
				case -4: nWork = 3; break;
				case -5: nWork = 2; break;
				case -6: nWork = 1; break;
				}

				nNow_SetTexture[i] = nNow_SetTexture[nWork] - 1;

				if (nNow_SetTexture[i] < 0)
					nNow_SetTexture[i] = nAll_Music_Num - 1;

			}

			// �ŏ�ɍs������ŉ��Ɉړ� + �W���P�b�g�����̂֍X�V
			//*********************************************************************
			if (Tex_2D_Data[i].Obj_Pos.x <= RIMIT_POSITION_UP.x + 10.0f &&
				Tex_2D_Data[i].Obj_Pos.x >= RIMIT_POSITION_UP.x - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y >= RIMIT_POSITION_UP.y - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y <= RIMIT_POSITION_UP.y + 10.0f)
			{
				Tex_2D_Data[i].Obj_Pos		= POSITION_CENTER_DOWN_SPEAR;
				Move_Vec[i].nMove_Vec_Up	= LEFT_UP;
				Move_Vec[i].nMove_Vec_Down	= RIGHT_DOWN;

				// �e�N�X�`���ԍ��ύX
				//*****************************************************************
				int nWork = i + 6;

				switch (nWork)
				{
				case  7: nWork = 0; break;
				case  8: nWork = 1; break;
				case  9: nWork = 2; break;
				case 10: nWork = 3; break;
				case 11: nWork = 4; break;
				case 12: nWork = 5; break;
				}

				nNow_SetTexture[i] = nNow_SetTexture[nWork] + 1;

				if (nNow_SetTexture[i] > nAll_Music_Num - 1)
					nNow_SetTexture[i] = 0;

			}
		}
	}

	if (!UP || !DOWN)
	{
		for (int i = 0; i < nObject_Num; i++)
		{
			Set_Move_Vec(Tex_2D_Data[i].Obj_Pos, i);
		}
	}

	CTexture_2D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
void MusicSelect_Jacket::Draw(int NUMBER)
{
	CTexture_2D_Base::Draw(NUMBER, nNow_SetTexture[NUMBER]);
}

//*************************************************************************
// �ړ��������Z�b�g
//*************************************************************************
void MusicSelect_Jacket::Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum)
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

				break;

			case 1:	// 1�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;

				break;

			case 2:	// 2�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				break;

			case 3:	// ��X�y�A
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				break;

			case 4:	// 1�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				break;

			case 5:	// 2�E��
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				break;

			case 6:	// ���X�y�A
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN_SPEAR;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
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
