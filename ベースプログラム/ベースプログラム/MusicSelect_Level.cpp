//*************************************************************************
//
// 曲セレクト画面・各難易度レベル
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "MusicSelect_Level.h" 
#include "Number.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
MusicSelect_Level::MusicSelect_Level(void)
{
	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num	= 42;

	// テクスチャを何種類使用するか？(最低 1～)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	0.0f, 0.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 43.0f, 72.0f );

		// テクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 0.1f, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red		=
		Tex_2D_Data[i].Green	=
		Tex_2D_Data[i].Brue		= 0;
		Tex_2D_Data[i].Alpha	= 255;

		// 画像の拡大率( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	MOVE_POSITION				= D3DXVECTOR3(  190.0f, 115.0f, 0.0f );	// オブジェクトが移動する際の移動距離
	RIMIT_POSITION_UP			= D3DXVECTOR3( 1498.0f, -32.0f, 0.0f );	// オブジェクト座標の上限
	POSITION_CENTER_UP_SPEAR	= D3DXVECTOR3( 1308.0f,  83.0f, 0.0f );	// オブジェクト上スペア座標
	POSITION_CENTER_UP_UP		= D3DXVECTOR3( 1118.0f, 198.0f, 0.0f );	// オブジェクトセンター2つ上座標
	POSITION_CENTER_UP			= D3DXVECTOR3(  928.0f, 313.0f, 0.0f );	// オブジェクトセンター1つ上座標
	POSITION_CENTER				= D3DXVECTOR3(  738.0f, 428.0f, 0.0f );	// オブジェクトセンター座標
	POSITION_CENTER_DOWN		= D3DXVECTOR3(  928.0f, 543.0f, 0.0f );	// オブジェクトセンター1つ下座標
	POSITION_CENTER_DOWN_DOWN	= D3DXVECTOR3( 1118.0f, 658.0f, 0.0f );	// オブジェクトセンター2つ下座標
	POSITION_CENTER_DOWN_SPEAR	= D3DXVECTOR3( 1308.0f, 773.0f, 0.0f );	// オブジェクト下スペア座標
	RIMIT_POSITION_DOWN			= D3DXVECTOR3( 1498.0f, 888.0f, 0.0f );	// オブジェクト座標の下限	

	// オブジェクトの初期位置指定・各難易度レベル初期化
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

			// 上スペア
			Tex_2D_Data[0 * 6 + i].Obj_Pos = POSITION_CENTER_UP_SPEAR;
			Tex_2D_Data[0 * 6 + i].Obj_Pos.x += Move;

			// 2つ右上
			Tex_2D_Data[1 * 6 + i].Obj_Pos = POSITION_CENTER_UP_UP;
			Tex_2D_Data[1 * 6 + i].Obj_Pos.x += Move;

			// 1つ右上
			Tex_2D_Data[2 * 6 + i].Obj_Pos = POSITION_CENTER_UP;
			Tex_2D_Data[2 * 6 + i].Obj_Pos.x += Move;

			// 中心
			Tex_2D_Data[3 * 6 + i].Obj_Pos = POSITION_CENTER;
			Tex_2D_Data[3 * 6 + i].Obj_Pos.x += Move;

			// １つ右下
			Tex_2D_Data[4 * 6 + i].Obj_Pos = POSITION_CENTER_DOWN;
			Tex_2D_Data[4 * 6 + i].Obj_Pos.x += Move;

			// 2つ右下
			Tex_2D_Data[5 * 6 + i].Obj_Pos = POSITION_CENTER_DOWN_DOWN;
			Tex_2D_Data[5 * 6 + i].Obj_Pos.x += Move;

			// 下スペア
			Tex_2D_Data[6 * 6 + i].Obj_Pos = POSITION_CENTER_DOWN_SPEAR;
			Tex_2D_Data[6 * 6 + i].Obj_Pos.x += Move;
			
		}
	}

	// 移動方向を指定
	//**********************************************************************
	{
		// 上スペア
		//**************************************
		Move_Vec[0].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[0].nMove_Vec_Down	= LEFT_DOWN;

		// ２つ右上
		//**************************************
		Move_Vec[1].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[1].nMove_Vec_Down	= LEFT_DOWN;

		// １つ右上
		//**************************************
		Move_Vec[2].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[2].nMove_Vec_Down	= LEFT_DOWN;

		// 中心
		//**************************************
		Move_Vec[3].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[3].nMove_Vec_Down	= RIGHT_DOWN;

		// １つ右下
		//**************************************
		Move_Vec[4].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[4].nMove_Vec_Down	= RIGHT_DOWN;

		// ２つ右下
		//**************************************
		Move_Vec[5].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[5].nMove_Vec_Down	= RIGHT_DOWN;

		// 下スペア
		//**************************************
		Move_Vec[6].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[6].nMove_Vec_Down	= RIGHT_DOWN;

	}


	// 全曲各難易度レベルを必要個数分確保・初期化
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
		// 各曲に入れるべきレベルを設定
		//**********************************************************************
		Music_Level[i].Easy_Level	= All_Level[i].Easy_Level;
		Music_Level[i].Hyper_Level	= All_Level[i].Hyper_Level;
		Music_Level[i].Master_Level = All_Level[i].Master_Level;
	}

	nOver_UP	= 0;
	nOver_DOWN	= 6;
	bOne_Flg	= true;

	CTexture_2D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 ～ 指定してください)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/共通使用/NUMBER.png", 0 );
	
}

//*************************************************************************
// デストラクタ
//*************************************************************************
MusicSelect_Level::~MusicSelect_Level(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void MusicSelect_Level::Update(bool UP, bool DOWN)
{
	// 全体上移動
	//*********************************************************************
	if ( UP )
	{
		//*****************************************************************
		// 移動処理
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

	// 全体下移動
	//*********************************************************************
	if ( DOWN )
	{
		//*****************************************************************
		// 移動処理
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

	// 最下に行ったら最上に移動
	// ＋各難易度テクスチャを変更
	//*********************************************************************
	int Level_Work	= 0;
	int Temp		= 0;


	//*********************************************************************
	// シーン開始時に一度のみ変更
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

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 0].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 1].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case HYPER:
					Level_Work = All_Level[i].Hyper_Level;

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 2].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 3].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case MASTER:
					Level_Work = All_Level[i].Master_Level;

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 4].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
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

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 0].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 1].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case HYPER:
					Level_Work = All_Level[nOver_UP].Hyper_Level;

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 2].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 3].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case MASTER:
					Level_Work = All_Level[nOver_UP].Master_Level;

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 4].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
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

	// 最上に行ったら最下に移動
	// ＋各難易度テクスチャを変更
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

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 0].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 1].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case HYPER:
					Level_Work = All_Level[nOver_DOWN].Hyper_Level;

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 2].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
					//*****************************
					Temp = Level_Work % 10 / 1;
					Tex_2D_Data[i * 6 + 3].Tex_Pos = Get_Number_Tex(Temp);

					break;

				case MASTER:
					Level_Work = All_Level[nOver_DOWN].Master_Level;

					// 十の位
					//*****************************
					Temp = Level_Work / 10;
					Tex_2D_Data[i * 6 + 4].Tex_Pos = Get_Number_Tex(Temp);


					// 一の位
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
// 描画処理
//*************************************************************************
void MusicSelect_Level::Draw(int NUM)
{
	for ( int i = 0 ; i < 6 ; i ++ )
	{
		CTexture_2D_Base::Draw( NUM * 6 + i, 0 );
	}
}

//*************************************************************************
// 移動方向をセット
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
			case 0:	// センター
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

			case 1:	// 1つ右上
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

			case 2:	// 2つ右上
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

			case 3:	// 上スペア
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

			case 4:	// 1つ右下
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

			case 5:	// 2つ右下
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

			case 6:	// 下スペア
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
// レベルセット
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
