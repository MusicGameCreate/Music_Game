//*************************************************************************
//
// ここにオブジェクトの説明
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "GameMain_HiSpeed.h" 
#include <math.h>

//*************************************************************************
// コンストラクタ
//*************************************************************************
GameMain_HiSpeed::GameMain_HiSpeed(void)
{
	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num	= 4;

	// テクスチャを何種類使用するか？(最低 1～)
	//**********************************************************************
	nUse_Texture_Num = 3;

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
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 0.0f, 0.0f );

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

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 ～ 指定してください)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/cross.png", 0);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/dot.png", 1);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/共通使用/NUMBER.png", 2);

	fNow_Speed = 2.5f;
	nAdd_Speed = 0;
}

//*************************************************************************
// デストラクタ
//*************************************************************************
GameMain_HiSpeed::~GameMain_HiSpeed(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void GameMain_HiSpeed::Update(void)
{
	if (CInput::GetKeyboardData(DIK_RSHIFT, PRESS))
	{	// 右シフト押下中は指定位置まで移動
		nAdd_Speed = -5;

		if (Tex_2D_Data[0].Obj_Pos.y <= 605.0f)
		{
			nAdd_Speed = 0;
		}

		// 右シフトを押しながら左右キーでハイスピの増減
		if (CInput::GetKeyboardData(DIK_LEFT, TRIGGER))
		{	// 減
			fNow_Speed -= 0.100f;
		}
		if (CInput::GetKeyboardData(DIK_RIGHT, TRIGGER))
		{	// 増
			fNow_Speed += 0.100f;
		}

		// 下限設定
		if ( fNow_Speed <= 1.000f )
		{
			fNow_Speed = 1.000f;
		}
		// 上限設定
		if ( fNow_Speed >= 7.000f )
		{
			fNow_Speed = 7.000f;
		}

	}

	if (CInput::GetKeyboardData(DIK_RSHIFT, RELEASE))
	{	// 右シフト離した瞬間に画面外へ
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

	// 移動処理
	for (int i = 0; i < nObject_Num; i++)
	{
		Tex_2D_Data[i].Obj_Pos.y += nAdd_Speed;
	}

	int nNum;

	// 左桁のテクスチャセット
	nNum = (int)(fNow_Speed / 1);
	Tex_2D_Data[1].Tex_Pos.x = (float)nNum * 0.100f;

	// 右桁のテクスチャセット
	nNum = (int)( fNow_Speed * 10.000f );
	nNum = nNum % 10 / 1;
	Tex_2D_Data[3].Tex_Pos.x = (float)nNum * 0.100f;

	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void GameMain_HiSpeed::Draw(void)
{
	CTexture_2D_Base::Draw(0, 0);	// X
	CTexture_2D_Base::Draw(1, 2);	// ○
	CTexture_2D_Base::Draw(2, 1);	// .
	CTexture_2D_Base::Draw(3, 2);	// ○
}

//*************************************************************************
// EOF
//*************************************************************************
