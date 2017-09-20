//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Title_Back.h"
#include "CMusic_Manager.h"

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
Title_Back::Title_Back()
{
	// オブジェクトを何個生成するか？(最低 1〜)
	nObject_Num = 3;
	nUse_Texture_Num = 3;

	// オブジェクトの個数分、必要なサイズを確保
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3( 100 + i * 200 , 200 , 0.0f);

		// オブジェクトのサイズ(X,Y)
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 100, 100 );

		// テクスチャ座標(0.0f〜1.0f)
		Tex_2D_Data[i].Tex_Pos	= D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f〜1.0f)
		Tex_2D_Data[i].Tex_Anim	= D3DXVECTOR2(1.0f, 1.0f);

		// 画像のRGBA値
		Tex_2D_Data[i].Red		= 
		Tex_2D_Data[i].Green	=
		Tex_2D_Data[i].Brue		= 
		Tex_2D_Data[i].Alpha	= 255;

		// 画像の拡大率(0.0f〜)
		Tex_2D_Data[i].fScale	= 1.0f;

		// 画像の回転角度(0.0f〜)
		Tex_2D_Data[i].fRot		= 0.0f;
	}

	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/Title.png", 0);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/Game.png", 1);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/Option.png", 2);
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
Title_Back::~Title_Back()
{
	CTexture_2D_Base::Finalise();
}

//***********************************************************************************************************
// 更新処理
//***********************************************************************************************************
void Title_Back::Update()
{

	CTexture_2D_Base::Update();
}

//***********************************************************************************************************
// 描画処理
//***********************************************************************************************************
void Title_Back::Draw()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		CTexture_2D_Base::Draw( i, i );
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************