//*************************************************************************
//
// ここにオブジェクトの説明
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "MusicSelect_RightFrame.h" 

//*************************************************************************
// コンストラクタ
//*************************************************************************
MusicSelect_RightFrame::MusicSelect_RightFrame(void)
{
	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num	= 7;

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
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3( 770.0f, 365.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 700.0f, 230.0f);

		// テクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red		=
		Tex_2D_Data[i].Green	=
		Tex_2D_Data[i].Brue		=
		Tex_2D_Data[i].Alpha	= 255;

		// 画像の拡大率( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fScale	= 1.0f;

		// 画像の回転角度( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fRot		= 0.0f;

		// 移動方向リセット
		//******************************************************************
		Move_Vec[i].nMove_Vec_Up	= NULL;
		Move_Vec[i].nMove_Vec_Down	= NULL;
	}

	// オブジェクトの初期位置指定
	//**********************************************************************
	{
		// 上スペア
		Tex_2D_Data[0].Obj_Pos = POSITION_CENTER_UP_SPEAR;
		// 2つ右上
		Tex_2D_Data[1].Obj_Pos = POSITION_CENTER_UP_UP;
		// 1つ右上
		Tex_2D_Data[2].Obj_Pos = POSITION_CENTER_UP;
		// 中心
		Tex_2D_Data[3].Obj_Pos = POSITION_CENTER;
		// １つ右下
		Tex_2D_Data[4].Obj_Pos = POSITION_CENTER_DOWN;
		// 2つ右下
		Tex_2D_Data[5].Obj_Pos = POSITION_CENTER_DOWN_DOWN;
		// 下スペア
		Tex_2D_Data[6].Obj_Pos = POSITION_CENTER_DOWN_SPEAR;
	}

	// 移動方向を指定
	//**********************************************************************
	{
		// 上スペア
		//**************************************
		Move_Vec[0].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[0].nMove_Vec_Down	= LEFT_DOWN;
		Move_Vec[0].nDraw_Order		= 0;

		// ２つ右上
		//**************************************
		Move_Vec[1].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[1].nMove_Vec_Down	= LEFT_DOWN;
		Move_Vec[1].nDraw_Order		= 1;

		// １つ右上
		//**************************************
		Move_Vec[2].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[2].nMove_Vec_Down	= LEFT_DOWN;
		Move_Vec[2].nDraw_Order		= 2;

		// 中心
		//**************************************
		Move_Vec[3].nMove_Vec_Up	= RIGHT_UP;
		Move_Vec[3].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[3].nDraw_Order		= 6;

		// １つ右下
		//**************************************
		Move_Vec[4].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[4].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[4].nDraw_Order		= 5;

		// ２つ右下
		//**************************************
		Move_Vec[5].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[5].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[5].nDraw_Order		= 4;

		// 下スペア
		//**************************************
		Move_Vec[6].nMove_Vec_Up	= LEFT_UP;
		Move_Vec[6].nMove_Vec_Down	= RIGHT_DOWN;
		Move_Vec[6].nDraw_Order		= 3;

	}

	CTexture_2D_Base::Init();

	// テクスチャ読み込み
	//**********************************************************************
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/MusicSelect/右曲情報枠.png", 0 );
}

//*************************************************************************
// デストラクタ
//*************************************************************************
MusicSelect_RightFrame::~MusicSelect_RightFrame(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void MusicSelect_RightFrame::Update(int DIFFICULT, bool UP, bool DOWN)
{
	// 全体上移動
	//*********************************************************************
	if ( UP )
	{
		//*****************************************************************
		// 移動処理
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

	 // 全体下移動
	 //*********************************************************************
	if ( DOWN )
	{
		//*****************************************************************
		// 移動処理
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


	 // 最下に行ったら最上に移動
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


	// 最上に行ったら最下に移動
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

	// 難易度に合わせて枠の色を変更
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
// 描画処理
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
// 移動方向をセット
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
			case 0:	// センター
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 6;

				break;

			case 1:	// 1つ右上
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 2;

				break;

			case 2:	// 2つ右上
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 1;

				break;

			case 3:	// 上スペア
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 0;

				break;

			case 4:	// 1つ右下
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 5;

				break;

			case 5:	// 2つ右下
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				Move_Vec[nNum].nDraw_Order		= 4;

				break;

			case 6:	// 下スペア
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
