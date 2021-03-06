//*************************************************************************
//
// 曲セレクト画面・スコア
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "MusicSelect_Score.h" 
#include "Number.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
MusicSelect_Score::MusicSelect_Score(void)
{
	// オブジェクトを何個作成するか？(最低 1〜)
	//**********************************************************************
	nObject_Num = 7;

	// テクスチャを何種類使用するか？(最低 1〜)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos = D3DXVECTOR3(63.0f + i * 44.0f, 247.0f, 0.0f);

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size = D3DXVECTOR2(53.0f, 79.0f);

		// テクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(0.1f, 1.0f);

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red =
			Tex_2D_Data[i].Green =
			Tex_2D_Data[i].Brue =
			Tex_2D_Data[i].Alpha = 255;

		// 画像の拡大率( 0.0f〜 )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度( 0.0f〜 )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	Tex_2D_Data[4].Obj_Pos = Tex_2D_Data[5].Obj_Pos = Tex_2D_Data[6].Obj_Pos = D3DXVECTOR3(231.0f, 261.0f, 0.0f);
	Tex_2D_Data[4].Obj_Size = Tex_2D_Data[5].Obj_Size = Tex_2D_Data[6].Obj_Size = D3DXVECTOR2(40.0f, 50.0f);
	Tex_2D_Data[5].Obj_Pos.x += 35.0f;
	Tex_2D_Data[6].Obj_Pos.x += 70.0f;


	CTexture_2D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 〜 指定してください)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/共通使用/NUMBER.png", 0);

	// SCOREの値初期化
	//*****************************
	SCORE = 0;
	SCORE_Temp = 0;
}

//*************************************************************************
// デストラクタ
//*************************************************************************
MusicSelect_Score::~MusicSelect_Score(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void MusicSelect_Score::Update(int nScore)
{
	int Temp;

	SCORE_Temp = nScore;

	if (SCORE != SCORE_Temp)
	{
		if (SCORE > SCORE_Temp)
		{
			SCORE -= rand() % 5000 + 4000;

			if (SCORE <= SCORE_Temp)
			{
				SCORE = SCORE_Temp;
			}
		}

		if (SCORE < SCORE_Temp)
		{
			SCORE += rand() % 5000 + 4000;

			if (SCORE >= SCORE_Temp)
			{
				SCORE = SCORE_Temp;
			}
		}
	}

	for (int i = 0; i < nObject_Num; i++)
	{
		switch (i)
		{
		case 0:	// 百万の位
			Temp = SCORE / 1000000;
			break;

		case 1:	// 十万の位
			Temp = SCORE % 1000000 / 100000;
			break;

		case 2:	// 一万の位
			Temp = SCORE % 1000000 % 100000 / 10000;
			break;

		case 3:	// 千の位
			Temp = SCORE % 1000000 % 100000 % 10000 / 1000;
			break;

		case 4:	// 百の位
			Temp = SCORE % 1000000 % 100000 % 10000 % 1000 / 100;
			break;

		case 5:	// 十の位
			Temp = SCORE % 1000000 % 100000 % 10000 % 1000 % 100 / 10;
			break;

		case 6:	// 一の位
			Temp = SCORE % 1000000 % 100000 % 10000 % 1000 % 100 % 10 / 1;
			break;
		}

		// 数字に対応したテクスチャ座標をセット
		//*****************************************************************
		Tex_2D_Data[i].Tex_Pos = Get_Number_Tex(Temp);
	}

	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void MusicSelect_Score::Draw(void)
{
	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_2D_Base::Draw(i, 0);
	}
}

//*************************************************************************
// EOF
//*************************************************************************