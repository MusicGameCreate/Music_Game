// フェード画面描画オブジェクト(2D描画基本クラスを継承)( CTexture_2D_Base )
// 表現を変えるかもなので要変更

#include "Fade_Background.h"

//******************************
// コンストラクタ
//******************************
Fade_Background::Fade_Background()				
{
	// オブジェクトを何個使用するか？(最低 1～)
	nObject_Num		= 1;

	// α値を増減させるために使用(要変更)
	nAddAlpha	= 5;

	//for( int i = 0 ; i < nObject_Num ; i ++ )
	//{
	//	// 座標(画像の中心を原点)
	//	Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	SCREEN_WIDTH / 2,
	//											SCREEN_HEIGHT / 2,
	//											0.0f );

	//	// オブジェクトのサイズ(X,Y)
	//	Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( SCREEN_WIDTH, SCREEN_HEIGHT );

	//	// テクスチャ座標(0.0f～1.0f)
	//	Tex_2D_Data[i].Tex_Pos	= D3DXVECTOR2( 0.0f, 0.0f );
	//
	//	// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
	//	Tex_2D_Data[i].Tex_Anim	= D3DXVECTOR2( 1.0f, 1.0f );

	//	// 画像のアルファ
	//	Tex_2D_Data[i].Alpha	= 0;

	//	// 画像の拡大率(0.0f～)
	//	Tex_2D_Data[i].fScale	= 1.0f;

	//	// 画像の回転角度(0.0f～)
	//	Tex_2D_Data[i].fRot		= 0.0f;
	//}
	
	nFrameCnt	= 0;
	bFrame		= false;

	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/フェード画面用/Fade.png", 0 );
}

//******************************
// デストラクタ
//******************************
Fade_Background::~Fade_Background()
{
	CTexture_2D_Base::Finalise();
}

//******************************
// 更新
//******************************
void Fade_Background::Update()
{

}

//******************************
// 描画
//******************************
void Fade_Background::Draw()
{
	CTexture_2D_Base::Draw(0,0);
}