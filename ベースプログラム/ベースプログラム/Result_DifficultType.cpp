//*************************************************************************
//
// リザルト画面・難易度文字
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "Result_DifficultType.h" 
#include "Alphabet.h"
#include "DirectX_Library.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
Result_DifficultType::Result_DifficultType(int nData)
{

	// 難易度の種類を格納
	//**********************************************************************
	nDifficult_Type = nData;

	{	// 難易度別処理
		if (nDifficult_Type == 0)
		{	// EASY処理
			nObject_Num = 4;
			Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

			Tex_2D_Data[0].Tex_Pos = Get_Alphabet_Tex("E");
			Tex_2D_Data[1].Tex_Pos = Get_Alphabet_Tex("A");
			Tex_2D_Data[2].Tex_Pos = Get_Alphabet_Tex("S");
			Tex_2D_Data[3].Tex_Pos = Get_Alphabet_Tex("Y");
		}

		if (nDifficult_Type == 1)
		{	// HYPER処理
			nObject_Num = 5;
			Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

			Tex_2D_Data[0].Tex_Pos = Get_Alphabet_Tex("H");
			Tex_2D_Data[1].Tex_Pos = Get_Alphabet_Tex("Y");
			Tex_2D_Data[2].Tex_Pos = Get_Alphabet_Tex("P");
			Tex_2D_Data[3].Tex_Pos = Get_Alphabet_Tex("E");
			Tex_2D_Data[4].Tex_Pos = Get_Alphabet_Tex("R");
		}

		if (nDifficult_Type == 2)
		{	// MASTER処理
			nObject_Num = 6;
			Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

			Tex_2D_Data[0].Tex_Pos = Get_Alphabet_Tex("M");
			Tex_2D_Data[1].Tex_Pos = Get_Alphabet_Tex("A");
			Tex_2D_Data[2].Tex_Pos = Get_Alphabet_Tex("S");
			Tex_2D_Data[3].Tex_Pos = Get_Alphabet_Tex("T");
			Tex_2D_Data[4].Tex_Pos = Get_Alphabet_Tex("E");
			Tex_2D_Data[5].Tex_Pos = Get_Alphabet_Tex("R");
		}
	}

	// テクスチャを何種類使用するか？(最低 1～)
	//**********************************************************************
	nUse_Texture_Num = 2;

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	45.0f + 35.0f * i, 280.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 40.0f, 40.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( Get_Alphabet_Texture_Width(), Get_Alphabet_Texture_Height() );

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

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 ～ 指定してください)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/共通使用/ALPHABET.png", 0 );

	// 難易度別に加工画像をロード
	//**********************************************************************
	if (nDifficult_Type == 0)
		CREATE_TEXTURE( pTexture[1], 0xff55ff55 );
	if (nDifficult_Type == 1)
		CREATE_TEXTURE( pTexture[1], 0xffffff00 );
	if (nDifficult_Type == 2)
		CREATE_TEXTURE( pTexture[1], 0xffff3737 );
}

//*************************************************************************
// デストラクタ
//*************************************************************************
Result_DifficultType::~Result_DifficultType(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void Result_DifficultType::Update(void)
{

	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void Result_DifficultType::Draw(void)
{
	CTexture_2D_Base::Texture_Blend( 1,1, ADD );

	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_2D_Base::Draw(i, 0);
	}

	CTexture_2D_Base::Texture_Blend( 1, NULL, NULL );
}

//*************************************************************************
// EOF
//*************************************************************************
