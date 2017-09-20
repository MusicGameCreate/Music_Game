//*************************************************************************
//
// フォント作成基底クラス
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "CFont_Base.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
CFont_Base::CFont_Base(void)
{
	// とりあえずNULLに
	//*********************************************************************
	pTexture	= NULL;
	aVertex		= NULL;

	// オブジェクト数は最初は1に設定
	//*********************************************************************
	nObject_Num = 1;

	// テクスチャ数は最初は1に設定
	//*********************************************************************
	nUse_Texture_Num = 1;
}

//*************************************************************************
// デストラクタ
//*************************************************************************
CFont_Base::~CFont_Base(void)
{

}

//*************************************************************************
// 初期化処理
//*************************************************************************
void CFont_Base::Init(int FONT_SIZE)
{
	int nFont_Weight = 500;

	LOGFONT LFONT = {	FONT_SIZE,					// フォント1文字の大きさ
						0,							//
						0,							// 
						0,							// 
						nFont_Weight, 				// フォントの太さ
						0, 							// 
						0, 							// 
						0, 							// 
						SHIFTJIS_CHARSET,			// 
						OUT_TT_ONLY_PRECIS, 		// 
						CLIP_DEFAULT_PRECIS, 		// 
						PROOF_QUALITY, 				// 
						DEFAULT_PITCH | FF_MODERN, 	// 
						"ＭＳ Ｐゴシック"			// フォント種類設定
					};

	hFONT = CreateFontIndirect(&LFONT);

	// オブジェクトの個数分、必要なサイズを確保
	// 頂点数 * 個数分 = 必要なオブジェクト分の頂点数(前から4個ずつ使用)
	//*********************************************************************
	aVertex = new VERTEX_2D[nObject_Num * NUM_VERTEX];

	// 頂点情報初期化
	//*********************************************************************
	MakeVertex();
}

//*************************************************************************
// 文字テクスチャ作成
//*************************************************************************
void CFont_Base::Create_Texture(wchar_t* FONT_CHAR, int nLength)
{
	// テクスチャを必要な文字列分確保
	//*********************************************************************
	pTexture = new LPDIRECT3DTEXTURE9[nLength];

	float fPos_X = 0.0f;

	for (int i = 0; i < nLength; i++)
	{
		//***********************************************************************************
		// フォントビットマップを生成↓
		//***********************************************************************************

		// 現在のウィンドウに適用
		// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
		HDC   hdc		= GetDC(NULL);
		HFONT oldFont	= (HFONT)SelectObject(hdc, hFONT);


		UINT code = (UINT)FONT_CHAR[i];

		const int gradFlag = GGO_GRAY8_BITMAP; // GGO_GRAY2_BITMAP or GGO_GRAY4_BITMAP or GGO_GRAY8_BITMAP

		int grad = 0; // 階調の最大値

		switch (gradFlag)
		{
		case GGO_GRAY2_BITMAP: grad = 4;  break;
		case GGO_GRAY4_BITMAP: grad = 16; break;
		case GGO_GRAY8_BITMAP: grad = 64; break;
		}

		TEXTMETRIC tm;
		GetTextMetrics( hdc, &tm );

		GLYPHMETRICS gm;


		CONST MAT2 mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };

		DWORD size = GetGlyphOutlineW( hdc, code, gradFlag, &gm, 0, NULL, &mat );



		BYTE* pMono = new BYTE[size];

		GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);

		// gm.gmBlackBoxX　　　→フォントビットマップ幅
		// gm.gmBlackBoxY　　　→フォントビットマップ高さ
		// gm.gmptGlyphOrigin　→フォントビットマップの原点からの左上相対位置
		//
		//

		//*********************************************************************
		// 幅と高さ、オフセット値、マージンを算出
		//*********************************************************************
		int Bitmap_Offset_X = gm.gmptGlyphOrigin.x;
		int Bitmap_Offset_Y = tm.tmAscent - gm.gmptGlyphOrigin.y;
		int Bitmap_Width	= gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
		int Bitmap_Height	= gm.gmBlackBoxY;

		//*********************************************************************
		// フォントの幅・高さを適切なサイズに変更
		//*********************************************************************
		Font_Data[i].Obj_Size.x = (float)Bitmap_Width + 2.0f;
		Font_Data[i].Obj_Size.y = (float)Bitmap_Height + 2.0f;


		//*********************************************************************
		// フォントの描画位置を適切な位置に変更
		//*********************************************************************
		Font_Data[i].Obj_Pos.x = Standard_Pos.x + fPos_X;
		Font_Data[i].Obj_Pos.y = Standard_Pos.y + (float)Bitmap_Offset_Y;

		//*********************************************************************
		// 次回のフォントの描画位置のため加算
		//*********************************************************************
		fPos_X += (float)Bitmap_Width;

		// デバイスコンテキストとフォントハンドルはもういらないので解放
		//*********************************************************************
		SelectObject(hdc, oldFont);
		ReleaseDC(NULL, hdc);

		//***********************************************************************************
		// フォントビットマップ生成終了↑
		//***********************************************************************************

		//***********************************************************************************
		// テクスチャ作成↓
		//***********************************************************************************
		CDirectX::Get_pD3DDevice()->CreateTexture(	Bitmap_Width + 2,	// テクスチャ幅
													Bitmap_Height + 2,	// テクスチャ高さ
													1,					//
													D3DUSAGE_DYNAMIC,	//
													D3DFMT_A8R8G8B8,	//
													D3DPOOL_DEFAULT,	//
													&pTexture[i],		// 作成するテクスチャ番地
													NULL);				//

		//***********************************************************************************
		// テクスチャ作成終了↑
		//***********************************************************************************

		//***********************************************************************************
		// BMPをテクスチャに適用↓
		//***********************************************************************************
		
		//***********************************************************************************
		// テクスチャにフォントビットマップ情報を書き込み↓
		//***********************************************************************************
		D3DLOCKED_RECT lockedRect;

		// ロック
		//*********************************************************************
		pTexture[i]->LockRect( 0, &lockedRect, NULL, D3DLOCK_DISCARD );

		memset(lockedRect.pBits, 0, lockedRect.Pitch * (Bitmap_Height + 2));

		DWORD *pTexBuf = (DWORD*)lockedRect.pBits;	// テクスチャメモリへのポインタ
		
		DWORD Alpha, Color;

		int X_Work = 0;
		int Y_Work = 0;

		for ( int y = 0 ; y < Bitmap_Height + 2 ; y ++ )
		{
			for ( int x = 0 ; x < Bitmap_Width + 2 ; x ++ )
			{

				// ↓要変更

				// テクスチャの最上・最下・最左・最右は真透明にする
				if ( y == 0 || y == Bitmap_Height + 1 || x == 0 || x == Bitmap_Width + 1 )
				{
					// (デバッグ)文字枠表示
					//Color = 0x00ffffff | (255 << 24) | 0x33000000;
					
					// 真透明に
					Color = 0x00000000;
				}
				else
				{
					Alpha = ( 255 * pMono[ X_Work + Bitmap_Width * Y_Work ] ) / grad;

					X_Work++;

					if ( X_Work == Bitmap_Width )
					{
						X_Work = 0;
						Y_Work ++;
					}

					Color = 0x00ffffff | (Alpha << 24);
				}

				memcpy((BYTE*)lockedRect.pBits + lockedRect.Pitch*y + 4 * x, &Color, sizeof(DWORD));

			}
		}

		// アンロック
		//*********************************************************************
		pTexture[i]->UnlockRect(0);

		delete[] pMono;
	}
}

//*************************************************************************
// 終了処理
//*************************************************************************
void CFont_Base::Finalise(int LENGTH)
{

	if ( pTexture != NULL )
	{	// テクスチャの解放
		for ( int i = 0 ; i < LENGTH ; i ++ )
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if ( Font_Data != NULL )
	{	// テクスチャ情報配列の解放
		delete[] Font_Data;
		Font_Data = NULL;
	}

	if ( aVertex != NULL )
	{	// 頂点情報配列の解放
		delete[] aVertex;
		aVertex = NULL;
	}
}

//*************************************************************************
// 更新処理
//*************************************************************************
void CFont_Base::Update(void)
{

	// 頂点座標更新
	//*********************************************************************
	SetVertex(); 		

	// テクスチャカラー情報更新
	//*********************************************************************
	SetColor();	 		

	// テクスチャ座標更新
	//*********************************************************************
	SetTexture();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void CFont_Base::Draw( int NUMBER, int SET_TEXTURE )
{
	CDirectX::Get_pD3DDevice()->SetFVF( FVF_VERTEX_2D );
	
	// テクスチャセット
	//*********************************************************************
	CDirectX::Get_pD3DDevice()->SetTexture( 0, pTexture[SET_TEXTURE] );
	
	// ポリゴンの描画
	//*********************************************************************
	CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(	D3DPT_TRIANGLESTRIP,			// プリミティブの種類
													NUM_POLYGON,					// ポリゴン数
													&aVertex[NUMBER * NUM_VERTEX],	// 配列の先頭アドレス
													sizeof(VERTEX_2D));				// 頂点のデータの大きさ
}

//*************************************************************************
// 頂点情報初期化
//*************************************************************************
void CFont_Base::MakeVertex()
{
	for (int i = 0; i < nObject_Num; i++)
	{
		// 頂点座標の設定
		//*****************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx =
		aVertex[i * NUM_VERTEX + 1].vtx =
		aVertex[i * NUM_VERTEX + 2].vtx =
		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		// rhwの設定(1.0固定)
		//*****************************************************************
		aVertex[i * NUM_VERTEX + 0].rhw =
		aVertex[i * NUM_VERTEX + 1].rhw =
		aVertex[i * NUM_VERTEX + 2].rhw =
		aVertex[i * NUM_VERTEX + 3].rhw = 1.0f;

		// 頂点カラーの設定(0～255)
		//*****************************************************************
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標
		//*****************************************************************
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}

//↓↓↓↓ テクスチャ情報更新関数( Private ) ↓↓↓↓

//*************************************************************************
//　頂点情報更新
//*************************************************************************
void CFont_Base::SetVertex()
{
	// 頂点座標の設定
	//*********************************************************************
	for (int i = 0; i < nObject_Num; i++)
	{
		aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	Font_Data[i].Obj_Pos.x,
														Font_Data[i].Obj_Pos.y,
														0.0f);

		aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	Font_Data[i].Obj_Pos.x + Font_Data[i].Obj_Size.x,
														Font_Data[i].Obj_Pos.y,
														0.0f);

		aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	Font_Data[i].Obj_Pos.x,
														Font_Data[i].Obj_Pos.y + Font_Data[i].Obj_Size.y,
														0.0f);

		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	Font_Data[i].Obj_Pos.x + Font_Data[i].Obj_Size.x,
														Font_Data[i].Obj_Pos.y + Font_Data[i].Obj_Size.y,
														0.0f);
	}
}

//*************************************************************************
//　テクスチャカラー情報更新
//*************************************************************************
void CFont_Base::SetColor()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA( Font_Data[i].Red,
														 Font_Data[i].Green,
														 Font_Data[i].Brue,
														 Font_Data[i].Alpha );
	}
}

//*************************************************************************
// テクスチャ座標更新
//*************************************************************************
void CFont_Base::SetTexture(void)
{
	for (int i = 0; i < nObject_Num; i++)
	{
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(	0.0f,
														0.0f );

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(	1.0f,
														0.0f );
		
		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(	0.0f,
														1.0f );
		
		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(	1.0f,
														1.0f );
	}
}

//*************************************************************************
// テクスチャ削除
//*************************************************************************
void CFont_Base::Delete_Texture(int LENGTH)
{

	if ( pTexture != NULL )
	{	// テクスチャの解放
		for ( int i = 0 ; i < LENGTH ; i ++ )
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

}

//*************************************************************************
// EOF
//*************************************************************************