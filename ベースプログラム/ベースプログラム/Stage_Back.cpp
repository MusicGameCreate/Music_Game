//************************************************
//インクルード部
//************************************************
#include "Stage_Back.h"

//************************************************
// コンストラクタ
//************************************************
Stage_Back::Stage_Back()
{
	// オブジェクトを何個使用するか？(最低 1～)
	nObj_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	Tex_2D_Data = new TEXTURE_2D_DATA[nObj_Num];
	aVertex = new VERTEX_2D[NUM_VERTEX * nObj_Num];

	for (int i = 0; i < nObj_Num; i++)
	{
		// 座標(画像の中心を原点)
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

		// オブジェクトのサイズ(X,Y)
		Tex_2D_Data[i].Obj_Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

		// テクスチャ座標(0.0f～1.0f)
		Tex_2D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// 画像のRGBA値
		Tex_2D_Data[i].Red = 255;
		Tex_2D_Data[i].Green = 255;
		Tex_2D_Data[i].Brue = 255;
		Tex_2D_Data[i].Alpha = 255;

		// 画像の拡大率(0.0f～)
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度(0.0f～)
		Tex_2D_Data[i].fRot = 0.0f;
	}

	CTexture_2D_Base::Init("../DATA/TEXTURE/Title.png");
}

//************************************************
// デストラクタ
//************************************************
Stage_Back::~Stage_Back()
{
	CTexture_2D_Base::Finalise();
}

//************************************************
// void Stage_Back::Update
// 説明：更新処理
// 引数：なし　戻り値：なし
//************************************************
void Stage_Back::Update()
{

	CTexture_2D_Base::Update();
}

//************************************************
// void Stage_Back::Draw
// 説明：描画処理
// 引数：なし　戻り値：なし
//************************************************
void Stage_Back::Draw()
{
	CTexture_2D_Base::Draw();
}