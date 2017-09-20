//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "GameMain_MusicDataFrame.h"

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
GameMain_MusicDataFrame::GameMain_MusicDataFrame()
{
	// オブジェクトを何個生成するか？(最低 1～)
	//*******************************************************************************************************
	nObject_Num = 2;

	// テクスチャを何種類使用するか？(最低 1～)
	//*******************************************************************************************************
	nUse_Texture_Num = 2;

	// オブジェクトの個数分、必要なサイズを確保
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0.0f);

		// オブジェクトのサイズ(X,Y)
		Tex_2D_Data[i].Obj_Size = D3DXVECTOR2(SCREEN_WIDTH, 160);

		// テクスチャ座標(0.0f～1.0f)
		Tex_2D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// 画像のRGBA値
		Tex_2D_Data[i].Red =
		Tex_2D_Data[i].Green =
		Tex_2D_Data[i].Brue = 
		Tex_2D_Data[i].Alpha = 255;

		// 画像の拡大率(0.0f～)
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度(0.0f～)
		Tex_2D_Data[i].fRot = 0.0f;
	}

	Tex_2D_Data[1].Alpha = 0;
	nFrameCount = 0;
	nAddAlpha = 5;

	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/曲情報枠_1.png", 0);
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/曲情報枠_2.png", 1);
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
GameMain_MusicDataFrame::~GameMain_MusicDataFrame()
{
	CTexture_2D_Base::Finalise();
}

//***********************************************************************************************************
// void GameMain_Back::Update
// 説明：更新処理
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void GameMain_MusicDataFrame::Update()
{
	Tex_2D_Data[1].Alpha += nAddAlpha;

	if (Tex_2D_Data[1].Alpha > 200 || Tex_2D_Data[1].Alpha <= 0)
	{
		nAddAlpha *= -1;
	}

	CTexture_2D_Base::Update();
}

//***********************************************************************************************************
// void GameMain_Back::Draw
// 説明：描画処理
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void GameMain_MusicDataFrame::Draw()
{
	CTexture_2D_Base::Draw(0, 0);

	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CTexture_2D_Base::Draw(1, 1);
}