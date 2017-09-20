//*************************************************************************
//
// 曲セレクト画面・ジャケット
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "MusicSelect_Jacket.h" 
#include "CMusic_Manager.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
MusicSelect_Jacket::MusicSelect_Jacket(void)
{
	// 曲データの総数を取得
	//**********************************************************************
	nAll_Music_Num = CMusic_Manager::Get_Music_Count();


	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num	= 7;

	// テクスチャを何種類使用するか？(最低 1～)
	//**********************************************************************
	nUse_Texture_Num = nAll_Music_Num;

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	// 曲総数分サイズ確保
	//**********************************************************************
	Jacket_Data = new JACKET_DATA[nAll_Music_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	0.0f, 0.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 160.0f, 160.0f );

		// テクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red  =
		Tex_2D_Data[i].Green=
		Tex_2D_Data[i].Brue =
		Tex_2D_Data[i].Alpha= 255;

		// 画像の拡大率( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;

		// 移動方向リセット
		//******************************************************************
		Move_Vec[i].nMove_Vec_Up	= NULL;
		Move_Vec[i].nMove_Vec_Down	= NULL;

		// 現在それぞれのオブジェクトにセットされているテクスチャ番号を格納
		//******************************************************************
		nNow_SetTexture[i] = i;

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


	CTexture_2D_Base::Init();


	// 全曲のジャケット画像の読み込み
	//**********************************************************************
	for (int i = 0; i < nAll_Music_Num; i++)
	{
		if ( CMusic_Manager::Get_MusicData(i)->Jacket_In == false )
		{
			// ジャケット画像が入っていない場合は仮の画像に差し替え
			//******************************************************************
			CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/共通使用/JACKET_ERROR.png", i);
		}
		else
		{
			// 曲のジャケットのパスを取得
			//******************************************************************
			Jacket_Data[i].Music_Jacket_Pass = CMusic_Manager::Get_MusicData(i)->Picture_Path;

			// 取得したジャケットのパスでテクスチャ読み込み
			//******************************************************************
			CTexture_2D_Base::Load_Texture(Jacket_Data[i].Music_Jacket_Pass, i);
		}

		// テクスチャ番号を格納
		//******************************************************************
		Jacket_Data[i].nTexture_Num = i;
	}
	
}

//*************************************************************************
// デストラクタ
//*************************************************************************
MusicSelect_Jacket::~MusicSelect_Jacket(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void MusicSelect_Jacket::Update(bool UP, bool DOWN)
{
	// テクスチャ左上座標
	D3DXVECTOR2 T1 = D3DXVECTOR2( ( 0.0f + 0.5f ) / 160.0f , 
								  ( 0.0f + 0.5f ) / 160.0f );

	D3DXVECTOR2 T2 = D3DXVECTOR2( ( 0.0f + 160.0f + 0.5f ) / 160.0f , 
								  ( 0.0f + 160.0f + 0.5f ) / 160.0f );

	for (int i = 0; i < nObject_Num; i++)
	{
		Tex_2D_Data[i].Tex_Pos  = T1;
		Tex_2D_Data[i].Tex_Anim = T2;
	}

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

	if ( !bMove_Down || !bMove_Up )
	{
		for (int i = 0; i < nObject_Num; i++)
		{
			// 最下に行ったら最上に移動 + ジャケットを次のへ更新
			//*********************************************************************
			if (Tex_2D_Data[i].Obj_Pos.x <= RIMIT_POSITION_DOWN.x + 10.0f &&
				Tex_2D_Data[i].Obj_Pos.x >= RIMIT_POSITION_DOWN.x - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y >= RIMIT_POSITION_DOWN.y - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y <= RIMIT_POSITION_DOWN.y + 10.0f)
			{
				Tex_2D_Data[i].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
				Move_Vec[i].nMove_Vec_Up	= RIGHT_UP;
				Move_Vec[i].nMove_Vec_Down	= LEFT_DOWN;

				// テクスチャ番号変更
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

			// 最上に行ったら最下に移動 + ジャケットを次のへ更新
			//*********************************************************************
			if (Tex_2D_Data[i].Obj_Pos.x <= RIMIT_POSITION_UP.x + 10.0f &&
				Tex_2D_Data[i].Obj_Pos.x >= RIMIT_POSITION_UP.x - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y >= RIMIT_POSITION_UP.y - 10.0f &&
				Tex_2D_Data[i].Obj_Pos.y <= RIMIT_POSITION_UP.y + 10.0f)
			{
				Tex_2D_Data[i].Obj_Pos		= POSITION_CENTER_DOWN_SPEAR;
				Move_Vec[i].nMove_Vec_Up	= LEFT_UP;
				Move_Vec[i].nMove_Vec_Down	= RIGHT_DOWN;

				// テクスチャ番号変更
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
// 描画処理
//*************************************************************************
void MusicSelect_Jacket::Draw(int NUMBER)
{
	CTexture_2D_Base::Draw(NUMBER, nNow_SetTexture[NUMBER]);
}

//*************************************************************************
// 移動方向をセット
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
			case 0:	// センター
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;

				break;

			case 1:	// 1つ右上
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;

				break;

			case 2:	// 2つ右上
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_UP;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				break;

			case 3:	// 上スペア
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_UP_SPEAR;
				Move_Vec[nNum].nMove_Vec_Up		= RIGHT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= LEFT_DOWN;
				break;

			case 4:	// 1つ右下
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				break;

			case 5:	// 2つ右下
				Tex_2D_Data[nNum].Obj_Pos		= POSITION_CENTER_DOWN_DOWN;
				Move_Vec[nNum].nMove_Vec_Up		= LEFT_UP;
				Move_Vec[nNum].nMove_Vec_Down	= RIGHT_DOWN;
				break;

			case 6:	// 下スペア
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
