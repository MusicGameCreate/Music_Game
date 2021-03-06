//*************************************************************************
// 
// 曲セレクト画面・ジャケット製作者フォント
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "MusicSelect_Illustrator.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
MusicSelect_Illustrator::MusicSelect_Illustrator(void)
{

	// オブジェクトを何個作成するか？(最低 1〜)
	//**********************************************************************
	nObject_Num = 20;


	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Font_Data = new FONT_DATA[nObject_Num];


	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Font_Data[i].Obj_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Font_Data[i].Obj_Size = D3DXVECTOR2(24.0f, 24.0f);

		// 画像のRGBA値
		//******************************************************************
		Font_Data[i].Red	=
		Font_Data[i].Green	=
		Font_Data[i].Brue	=
		Font_Data[i].Alpha	= 255;
	}

	// フォント描画の基準点を設定
	//******************************************************************
	Standard_Pos = D3DXVECTOR2( 50.0f, 435.0f );

	CFont_Base::Init(24);

	// 現在のフォント長さを初期化
	//******************************************************************
	Now_Illustrator_Length = 0;
}

//*************************************************************************
// デストラクタ
//*************************************************************************
MusicSelect_Illustrator::~MusicSelect_Illustrator(void)
{
	CFont_Base::Finalise( Now_Illustrator_Length );
}

//*************************************************************************
// 更新処理
//*************************************************************************
void MusicSelect_Illustrator::Update( wchar_t* FONT, int LENGTH ,bool CHANGE )
{
	if ( CHANGE )
	{
		CFont_Base::Delete_Texture(Now_Illustrator_Length);


		Now_Illustrator_Length = LENGTH;


		CFont_Base::Create_Texture(FONT, Now_Illustrator_Length);
	}

	CFont_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void MusicSelect_Illustrator::Draw(void)
{
	for ( int i = 0 ; i < Now_Illustrator_Length ; i ++ )
	{
		CFont_Base::Draw(i, i);
	}
	
}

//*************************************************************************
// EOF
//*************************************************************************