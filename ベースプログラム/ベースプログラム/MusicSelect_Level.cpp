//*************************************************************************
//
// �ȃZ���N�g��ʁE�e��Փx���x��
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "MusicSelect_Level.h" 
#include "Number.h"

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
MusicSelect_Level::MusicSelect_Level(void)
{
	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num	= 42;

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
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	0.0f, 0.0f, 0.0f );

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 43.0f, 72.0f );

		// �e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 0.1f, 1.0f );

		// �摜��RGBA�l
		//******************************************************************
		Tex_2D_Data[i].Red		=
		Tex_2D_Data[i].Green	=
		Tex_2D_Data[i].Brue		= 0;
		Tex_2D_Data[i].Alpha	= 255;

		// �摜�̊g�嗦( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// �摜�̉�]�p�x( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	MOVE_POSITION				= D3DXVECTOR3(  190.0f, 115.0f, 0.0f );	// �I�u�W�F�N�g���ړ�����ۂ̈ړ�����
	RIMIT_POSITION_UP			= D3DXVECTOR3( 1498.0f, -32.0f, 0.0f );	// �I�u�W�F�N�g���W�̏��
	POSITION_CENTER_UP_SPEAR	= D3DXVECTOR3( 1308.0f,  83.0f, 0.0f );	// �I�u�W�F�N�g��X�y�A���W
	POSITION_CENTER_UP_UP		= D3DXVECTOR3( 1118.0f, 198.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[2����W
	POSITION_CENTER_UP			= D3DXVECTOR3(  928.0f, 313.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[1����W
	POSITION_CENTER				= D3DXVECTOR3(  738.0f, 428.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[���W
	POSITION_CENTER_DOWN		= D3DXVECTOR3(  928.0f, 543.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[1�����W
	POSITION_CENTER_DOWN_DOWN	= D3DXVECTOR3( 1118.0f, 658.0f, 0.0f );	// �I�u�W�F�N�g�Z���^�[2�����W
	POSITION_CENTER_DOWN_SPEAR	= D3DXVECTOR3( 1308.0f, 773.0f, 0.0f );	// �I�u�W�F�N�g���X�y�A���W
	RIMIT_POSITION_DOWN			= D3DXVECTOR3( 1498.0f, 888.0f, 0.0f );	// �I�u�W�F�N�g���W�̉���	

	// �I�u�W�F�N�g�̏����ʒu�w��E�e��Փx���x��������
	//**********************************************************************
	{
		for ( int i = 0 ; i < 6 ; i ++ )
		{
			float Move = 0.0f;

			switch ( i )
			{
			case 0: Move = 0.0f;     break;
			case 1: Move = 40.0f;    break;
			case 2: Move = 105.0f;   break;
			case 3: Move = 145.0f;   break;
			case 4: Move = 210.0f;   break;
			case 5: Move = 250.0f;   break;
			}

			// ��X�y�A
			Tex_2D_Data[0 * 6 + i].Obj_Pos = POSITION_CENTER_UP_SPEAR;
			Tex_2D_Data[0 * 6 + i].Obj_Pos.x += Move;

			// 2�E��
			Tex_2D_Data[1 * 6 + i].Obj_Pos = POSITION_CENTER_UP_UP;
			Tex_2D_Data[1 * 6 + i].Obj_Pos.x += Move;

			// 1�E��
			Tex_2D_Data[2 * 6 + i].Obj_Pos = POSITION_CENTER_UP;
			Tex_2D_Data[2 * 6 + i].Obj_Pos.x += Move;

			// ���S
			Tex_2D_Data[3 * 6 + i].Obj_Pos = POSITION_CENTER;
			Tex_2D_Data[3 * 6 + i].Obj_Pos.x += Move;

			// �P�E��
			Tex_2D_Data[4 * 6 + i].Obj_Pos = POSITION_CENTER_DOWN;
			Tex_2D_Data[4 * 6 + i].Obj_Pos.x += Move;

			// 2�E��
			Tex_2D_Data[5 * 6 + i].Obj_Pos = POSITION_CENTER_DOWN_DOWN;
			Tex_2D_Data[5 * 6 + i].Obj_Pos.x += Move;

			// ���X�y�A
			Tex_2D_Data[6 * 6 + i].Obj_Pos = POSITION_CENTER_DOWN_SPEAR;
			Tex_2D_Data[6 * 6 + i].Obj_Pos.x += Move;
			
		}
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


	// �S�Ȋe��Փx���x����K�v�����m�ہE������
	//**********************************************************************
	All_Level = new MUSIC_LEVEL[CMusic_Manager::Get_Music_Count()];

	for (int i = 0; i < CMusic_Manager::Get_Music_Count(); i++)
	{
		All_Level[i].Easy_Level		= 0;
		All_Level[i].Hyper_Level	= 0;
		All_Level[i].Master_Level	= 0;
	}

	for ( int i = 0 ; i < 7 ; i ++ )
	{
		// �e�Ȃɓ����ׂ����x����ݒ�
		//**********************************************************************
		Music_Level[i].Easy_Level	= All_Level[i].Easy_Level;
		Music_Level[i].Hyper_Level	= All_Level[i].Hyper_Level;
		Music_Level[i].Master_Level = All_Level[i].Master_Level;
	}

	nOver_UP	= 0;
	nOver_DOWN	= 6;
	bOne_Flg	= true;

	CTexture_2D_Base::Init();

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/���ʎg�p/NUMBER.png", 0 );
	
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
MusicSelect_Level::~MusicSelect_Level(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void MusicSelect_Level::Update(bool UP, bool DOWN)
{
	// �S�̏�ړ�
	//*********************************************************************
	if ( UP )
	{
		//*****************************************************************
		// �ړ�����
		//*****************************************************************
		for ( int i = 0 ; i < 7 ; i ++ )
		{
			switch ( Move_Vec[i].nMove_Vec_Up )
			{
			case RIGHT_UP:
				
				for ( int j = 0 ; j < 6 ; j ++ )
				{
					Tex_2D_Data[i * 6 + j].Obj_Pos.x += (float)( MOVE_POSITION.x / 10 );
					Tex_2D_Data[i * 6 + j].Obj_Pos.y -= (float)( MOVE_POSITION.y / 10 );


				}

				break;

			case LEFT_UP:
				
				for ( int j = 0;  j < 6 ; j ++ )
				{
					Tex_2D_Data[i * 6 + j].Obj_Pos.x -= (float)( MOVE_POSITION.x / 10 );
					Tex_2D_Data[i * 6 + j].Obj_Pos.y -= (float)( MOVE_POSITION.y / 10 );


				}

				break;
			}
		}

	}

	// �S�̉��ړ�
	//*********************************************************************
	if ( DOWN )
	{
		//*****************************************************************
		// �ړ�����
		//*****************************************************************
		for ( int i = 0 ; i < 7 ; i ++ )
		{
			switch ( Move_Vec[i].nMove_Vec_Down )
			{
			case RIGHT_DOWN:

				for ( int j = 0 ; j < 6 ; j ++ )
				{
					Tex_2D_Data[i * 6 + j].Obj_Pos.x += (float)( MOVE_POSITION.x / 10 );
					Tex_2D_Data[i * 6 + j].Obj_Pos.y += (float)( MOVE_POSITION.y / 10 );


				}

				break;

			case LEFT_DOWN:

				for ( int j = 0 ; j < 6 ; j ++ )
				{
					Tex_2D_Data[i * 6 + j].Obj_Pos.x -= (float)( MOVE_POSITION.x / 10 );
					Tex_2D_Data[i * 6 + j].Obj_Pos.y += (float)( MOVE_POSITION.y / 10 );


				}

				break;
			}
		}
	}

	// �ŉ��ɍs������ŏ�Ɉړ�
	// �{�e��Փx�e�N�X�`����ύX
	//*********************************************************************
	int Level_Work	= 0;
	int Temp		= 0;


	//*********************************************************************
	// �V�[���J�n���Ɉ�x�̂ݕύX
	//*********************************************************************
	if ( bOne_Flg )
	{
		for ( int i = 0 ; i < 7 ; i ++ )
		{

			for ( int j = 0 ; j < 3 ; j ++ )
			{
				switch ( j )
				{

				case EASY:
					Level_Work = All_Level[i].Easy_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 0].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 1].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case HYPER:
					Level_Work = All_Level[i].Hyper_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 2].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 3].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case MASTER:
					Level_Work = All_Level[i].Master_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 4].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 5].Tex_Pos = Get_Number_Tex(Temp);

					break;
				}
			}

		}

		bOne_Flg = false;
	}

	for ( int i = 0 ; i < 7 ; i ++ )
	{
		if (Tex_2D_Data[i * 6].Obj_Pos.x <= RIMIT_POSITION_DOWN.x + 10.0f &&
			Tex_2D_Data[i * 6].Obj_Pos.x >= RIMIT_POSITION_DOWN.x - 10.0f &&
			Tex_2D_Data[i * 6].Obj_Pos.y >= RIMIT_POSITION_DOWN.y - 10.0f &&
			Tex_2D_Data[i * 6].Obj_Pos.y <= RIMIT_POSITION_DOWN.y + 10.0f)
		{
			nOver_UP--;

			if (nOver_UP <= -1)
			{
				nOver_UP = CMusic_Manager::Get_Music_Count() - 1;
			}

			nOver_DOWN--;

			if (nOver_DOWN <= -1)
			{
				nOver_DOWN = CMusic_Manager::Get_Music_Count() - 1;
			}

			for ( int j = 0 ; j < 6 ; j ++ )
			{
				float Move = 0.0f;

				switch ( j )
				{
				case 0: Move =   0.0f;   break;
				case 1: Move =  40.0f;   break;
				case 2: Move = 105.0f;   break;
				case 3: Move = 145.0f;   break;
				case 4: Move = 210.0f;   break;
				case 5: Move = 250.0f;   break;
				}

				Tex_2D_Data[i * 6 + j].Obj_Pos = POSITION_CENTER_UP_SPEAR;
				Tex_2D_Data[i * 6 + j].Obj_Pos.x += Move;
			}

			for (int j = 0; j < 3; j++)
			{
				switch (j)
				{

				case EASY:
					Level_Work = All_Level[nOver_UP].Easy_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 0].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 1].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case HYPER:
					Level_Work = All_Level[nOver_UP].Hyper_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 2].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 3].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case MASTER:
					Level_Work = All_Level[nOver_UP].Master_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 4].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 5].Tex_Pos = Get_Number_Tex(Temp);

					break;
				}
			}

			Move_Vec[i].nMove_Vec_Up	= RIGHT_UP;
			Move_Vec[i].nMove_Vec_Down	= LEFT_DOWN;
		}
	}

	// �ŏ�ɍs������ŉ��Ɉړ�
	// �{�e��Փx�e�N�X�`����ύX
	//*********************************************************************
	for ( int i = 0 ; i < 7 ; i ++ )
	{
		if (Tex_2D_Data[i * 6].Obj_Pos.x <= RIMIT_POSITION_UP.x + 10.0f &&
			Tex_2D_Data[i * 6].Obj_Pos.x >= RIMIT_POSITION_UP.x - 10.0f &&
			Tex_2D_Data[i * 6].Obj_Pos.y >= RIMIT_POSITION_UP.y - 10.0f &&
			Tex_2D_Data[i * 6].Obj_Pos.y <= RIMIT_POSITION_UP.y + 10.0f)
		{
			nOver_UP++;

			if ( nOver_UP >= CMusic_Manager::Get_Music_Count() )
			{
				nOver_UP = 0;
			}

			nOver_DOWN++;

			if ( nOver_DOWN >= CMusic_Manager::Get_Music_Count() )
			{
				nOver_DOWN = 0;
			}

			for (int j = 0; j < 6; j++)
			{
				float Move = 0.0f;

				switch (j)
				{
				case 0: Move =   0.0f;   break;
				case 1: Move =  40.0f;   break;
				case 2: Move = 105.0f;   break;
				case 3: Move = 145.0f;   break;
				case 4: Move = 210.0f;   break;
				case 5: Move = 250.0f;   break;
				}

				Tex_2D_Data[i * 6 + j].Obj_Pos = POSITION_CENTER_DOWN_SPEAR;
				Tex_2D_Data[i * 6 + j].Obj_Pos.x += Move;

			}

			for ( int j = 0 ; j < 3; j ++ )
			{
				switch (j)
				{
				
				case EASY:
					Level_Work = All_Level[nOver_DOWN].Easy_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 0].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 1].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case HYPER:
					Level_Work = All_Level[nOver_DOWN].Hyper_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 2].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 3].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case MASTER:
					Level_Work = All_Level[nOver_DOWN].Master_Level;

					// �\�̈�
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 4].Tex_Pos = Get_Number_Tex(Temp);


					// ��̈�
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 5].Tex_Pos = Get_Number_Tex(Temp);

					break;
				}
			}

			Move_Vec[i].nMove_Vec_Up	= LEFT_UP;
			Move_Vec[i].nMove_Vec_Down	= RIGHT_DOWN;
		}
	}

	if ( !UP || !DOWN )
	{
		for ( int i = 0 ; i < 7 ; i ++ )
		{
			int Work_ = i * 6;

			Set_Move_Vec( Tex_2D_Data[Work_].Obj_Pos, i , Work_ );
		}
	}

	CTexture_2D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
void MusicSelect_Level::Draw(int NUM)
{
	for ( int i = 0 ; i < 6 ; i ++ )
	{
		CTexture_2D_Base::Draw( NUM * 6 + i, 0 );
	}
}

//*************************************************************************
// �ړ��������Z�b�g
//*************************************************************************
void MusicSelect_Level::Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum, int Soezi)
{
	D3DXVECTOR3 POS[7];

	POS[0] = POSITION_CENTER;
	POS[1] = POSITION_CENTER_UP;
	POS[2] = POSITION_CENTER_UP_UP;
	POS[3] = POSITION_CENTER_UP_SPEAR;
	POS[4] = POSITION_CENTER_DOWN;
	POS[5] = POSITION_CENTER_DOWN_DOWN;
	POS[6] = POSITION_CENTER_DOWN_SPEAR;

	int Level_Work = 0;
	int Temp = 0;

	for ( int i = 0 ; i < 7 ; i ++ )
	{
		if (POSITION.x <= POS[i].x + 10.0f &&
			POSITION.x >= POS[i].x - 10.0f &&
			POSITION.y >= POS[i].y - 10.0f &&
			POSITION.y <= POS[i].y + 10.0f)
		{
			switch (i)
			{
			case 0:	// �Z���^�[
				for (int j = 0; j < 6; j++)
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;

				return;

			case 1:	// 1�E��
				for ( int j = 0 ; j < 6 ; j ++ )
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER_UP;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;

				return;

			case 2:	// 2�E��
				for (int j = 0; j < 6; j++)
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER_UP_UP;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;

				return;

			case 3:	// ��X�y�A
				for (int j = 0; j < 6; j++)
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER_UP_SPEAR;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;

				return;

			case 4:	// 1�E��
				for (int j = 0; j < 6; j++)
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER_DOWN;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;

				return;

			case 5:	// 2�E��
				for (int j = 0; j < 6; j++)
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER_DOWN_DOWN;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;

				return;

			case 6:	// ���X�y�A
				for (int j = 0; j < 6; j++)
				{
					float Move = 0.0f;

					switch (j)
					{
					case 0: Move =   0.0f;   break;
					case 1: Move =  40.0f;   break;
					case 2: Move = 105.0f;   break;
					case 3: Move = 145.0f;   break;
					case 4: Move = 210.0f;   break;
					case 5: Move = 250.0f;   break;
					}

					Tex_2D_Data[Soezi + j].Obj_Pos = POSITION_CENTER_DOWN_SPEAR;
					Tex_2D_Data[Soezi + j].Obj_Pos.x += Move;
				}

				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;

				return;

			default:
				break;
			}
		}
	}
}

//*************************************************************************
// ���x���Z�b�g
//*************************************************************************
void MusicSelect_Level::Set_Level(int LEVEL, int NUM, int DIFFICULT)
{
	switch ( DIFFICULT )
	{
	case   EASY: All_Level[NUM].Easy_Level	 = LEVEL; break;
	case  HYPER: All_Level[NUM].Hyper_Level	 = LEVEL; break;
	case MASTER: All_Level[NUM].Master_Level = LEVEL; break;
	}
}

//*************************************************************************
// EOF
//*************************************************************************
