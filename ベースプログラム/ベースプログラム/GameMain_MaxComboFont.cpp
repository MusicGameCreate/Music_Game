//*************************************************************************
//
// ゲームメイン画面・MAXCOMBO文字
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "GameMain_MaxComboFont.h" 

//*************************************************************************
// コンストラクタ
//*************************************************************************
GameMain_MaxComboFont::GameMain_MaxComboFont(void)
{
	// オブジェクトを何個作成するか？(最低 1〜)
	//**********************************************************************
	nObject_Num	= 1;

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
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	770.0f, 85.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 180.0f, 23.0f );

		// テクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red  =
		Tex_2D_Data[i].Green=
		Tex_2D_Data[i].Brue =
		Tex_2D_Data[i].Alpha= 255;

		// 画像の拡大率( 0.0f〜 )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度( 0.0f〜 )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	CTexture_2D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 〜 指定してください)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/GameMain/MaxCombo.png", 0 );
	
}

//*************************************************************************
// デストラクタ
//*************************************************************************
GameMain_MaxComboFont::~GameMain_MaxComboFont(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void GameMain_MaxComboFont::Update(void)
{
	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void GameMain_MaxComboFont::Draw(void)
{
	CTexture_2D_Base::Draw(0,0);
}

//*************************************************************************
// EOF
//*************************************************************************
