//*************************************************************************
//
// ここにオブジェクトの説明
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "GameMain_PushEffect.h" 

float fAnimetion = 1.0f / 7;

//*************************************************************************
// コンストラクタ
//*************************************************************************
GameMain_PushEffect::GameMain_PushEffect(void)
{
	// オブジェクトを何個作成するか？(最低 1〜)
	//**********************************************************************
	nObject_Num	= 2;

	// テクスチャを何種類使用するか？(最低 1〜)
	//**********************************************************************
	nUse_Texture_Num = 2;

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
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 100.0f, 100.0f );

		// テクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2(fAnimetion, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red =
		Tex_2D_Data[i].Green =
		Tex_2D_Data[i].Brue = 255;
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
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/GameMain/判定テクスチャ3.png",  0 );
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/GameMain/判定テクスチャ4.png", 1 );
	
}

//*************************************************************************
// デストラクタ
//*************************************************************************
GameMain_PushEffect::~GameMain_PushEffect(void)
{
	CTexture_2D_Base::Finalise();
}

int nCount = 0;

//*************************************************************************
// 更新処理
//*************************************************************************
void GameMain_PushEffect::Update(void)
{
	// 現在のマウスの座標を取得
	D3DXVECTOR3 pos = CInput::GetMousePos();

	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		Tex_2D_Data[i].Obj_Pos = pos;
	}

	nCount++;

	if (nCount > 3)
	{
		nCount = 0;

		for (int i = 0; i < nObject_Num; i++)
		{
			Tex_2D_Data[i].Tex_Pos.x += fAnimetion;

			if (Tex_2D_Data[i].Tex_Pos.x >= 1.0f)
				Tex_2D_Data[i].Tex_Pos.x = 0.0f;

		}
	}

	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void GameMain_PushEffect::Draw(void)
{
	CTexture_2D_Base::Draw(0, 0);

	CTexture_2D_Base::Draw(1, 1);
}

//*************************************************************************
// EOF
//*************************************************************************
