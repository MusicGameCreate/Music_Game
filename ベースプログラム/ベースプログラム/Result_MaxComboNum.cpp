//*************************************************************************
//
// リザルト画面・最大コンボ数
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "Result_MaxComboNum.h" 
#include "Number.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
Result_MaxComboNum::Result_MaxComboNum(int nData)
{
	// プレイ曲の最高コンボ数を格納
	//**********************************************************************
	nMaxComboNum = nData;

	// オブジェクトを何個作成するか？(最低 1〜)
	//**********************************************************************
	nObject_Num	= 3;

	// テクスチャを何種類使用するか？(最低 1〜)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	536.0f + i * 32.0f, 602.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 39.0f, 38.0f );

		// テクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 0.1f, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red  = Tex_2D_Data[i].Green= Tex_2D_Data[i].Brue = Tex_2D_Data[i].Alpha = 255;

		Tex_2D_Data[i].fScale	= 1.0f;
		Tex_2D_Data[i].fRot		= 0.0f;
	}

	CTexture_2D_Base::Init();

	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/共通使用/NUMBER.png", 0);
}

//*************************************************************************
// デストラクタ
//*************************************************************************
Result_MaxComboNum::~Result_MaxComboNum(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void Result_MaxComboNum::Update(void)
{
	int nNum;

	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		switch (i)
		{
		case 0: nNum = nMaxComboNum / 100;			break;
		case 1: nNum = nMaxComboNum % 100 / 10;		break;
		case 2:	nNum = nMaxComboNum % 100 % 10 / 1; break;
		}

		// 数字に対応したテクスチャ座標をセット
		//*****************************************************************
		Tex_2D_Data[i].Tex_Pos = Get_Number_Tex(nNum);
	}

	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void Result_MaxComboNum::Draw(void)
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		CTexture_2D_Base::Draw( i, 0 );
	}
}

//*************************************************************************
// EOF
//*************************************************************************
