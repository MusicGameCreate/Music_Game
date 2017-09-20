//************************************************
// インクルード部
//************************************************
#include "ModeSelect_Back.h"

//************************************************
// コンストラクタ
//************************************************
ModeSelect_Back::ModeSelect_Back()
{
	// オブジェクトを何個生成するか？(最低 1～)
	nObject_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 , 0.0f);

		// オブジェクトのサイズ(X,Y)
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2(600, 500);

		// テクスチャ座標(0.0f～1.0f)
		Tex_2D_Data[i].Tex_Pos	= D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// 画像のRGBA値
		Tex_2D_Data[i].Red		=
		Tex_2D_Data[i].Green	=
		Tex_2D_Data[i].Brue		= 
		Tex_2D_Data[i].Alpha	= 255;

		// 画像の拡大率(0.0f～)
		Tex_2D_Data[i].fScale	= 1.0f;

		// 画像の回転角度(0.0f～)
		Tex_2D_Data[i].fRot		= 0.0f;
	}

	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/Mode_Select.png", 0);
}

//************************************************
// デストラクタ
//************************************************
ModeSelect_Back::~ModeSelect_Back()
{
	CTexture_2D_Base::Finalise();
}

//************************************************
// void ModeSelect_Back::Update
// 説明：更新処理
// 引数：なし　戻り値：なし
//************************************************
void ModeSelect_Back::Update()
{
	if (CInput::GetKeyboardData(DIK_UP, PRESS))
	{
		Tex_2D_Data[0].Obj_Size.x += 1.0f;
		Tex_2D_Data[0].Obj_Size.y += 1.0f;
	}

	if (CInput::GetKeyboardData(DIK_DOWN, PRESS))
	{
		Tex_2D_Data[0].Obj_Size.x -= 1.0f;
		Tex_2D_Data[0].Obj_Size.y -= 1.0f;
	}

	CTexture_2D_Base::Update();
}

//************************************************
// void ModeSelect_Back::Draw
// 説明：描画処理
// 引数：なし　戻り値：なし
//************************************************
void ModeSelect_Back::Draw()
{
	CTexture_2D_Base::Draw(0,0);
}