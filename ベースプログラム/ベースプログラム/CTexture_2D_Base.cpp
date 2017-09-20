//***********************************************************************************************************
//
// 2D画像描画基本クラス
//
//***********************************************************************************************************


//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CTexture_2D_Base.h"


//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
CTexture_2D_Base::CTexture_2D_Base()
{
	// とりあえずNULLに
	//*******************************************************************************************************
	pTexture			= NULL;	// テクスチャ画像情報
	Tex_2D_Data			= NULL;	// テクスチャ情報配列
	aVertex				= NULL; // 頂点情報配列

	// オブジェクト数は最初は1に設定
	//*******************************************************************************************************
	nObject_Num			= 1;

	// テクスチャ数は最初は1に設定
	//*******************************************************************************************************
	nUse_Texture_Num	= 1;
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
CTexture_2D_Base::~CTexture_2D_Base()
{

}

//***********************************************************************************************************
// 初期化
//***********************************************************************************************************
void CTexture_2D_Base::Init()
{
	// オブジェクトの個数分、必要なサイズを確保
	// 頂点数 * 個数分 = 必要なオブジェクト分の頂点数(前から4個ずつ使用)
	//*******************************************************************************************************
	aVertex		= new VERTEX_2D[NUM_VERTEX * nObject_Num];

	// 使用テクスチャ分サイズを確保
	//*******************************************************************************************************
	pTexture	= new LPDIRECT3DTEXTURE9[nUse_Texture_Num];

	// 頂点情報初期化
	//*******************************************************************************************************
	MakeVertex();

}

//***********************************************************************************************************
// テクスチャ読み込み
//***********************************************************************************************************
void CTexture_2D_Base::Load_Texture( char* TEXTURE_FILE, int NUMBER )
{	
	//*******************************************************************************************************
	// 画像のサイズを取得
	//*******************************************************************************************************
	D3DXIMAGE_INFO	INFO;
	D3DXGetImageInfoFromFile( TEXTURE_FILE, &INFO );

	//*******************************************************************************************************
	// テクスチャの読み込み
	//*******************************************************************************************************
	D3DXCreateTextureFromFileEx(	CDirectX::Get_pD3DDevice(),
									TEXTURE_FILE,
									INFO.Width,
									INFO.Height,
									0,
									0,
									D3DFMT_UNKNOWN,
									D3DPOOL_DEFAULT,
									D3DX_FILTER_LINEAR,
									D3DX_DEFAULT,
									0,
									NULL,
									NULL,
									&pTexture[NUMBER] );
}

//***********************************************************************************************************
// テクスチャブレンド
//***********************************************************************************************************
void CTexture_2D_Base::Texture_Blend(int STAGE, int NUMBER, int TYPE)
{
	if( NUMBER != NULL )
		CDirectX::Get_pD3DDevice()->SetTexture( STAGE, pTexture[NUMBER] );
	else
		CDirectX::Get_pD3DDevice()->SetTexture( STAGE, NULL );

	// 加算合成タイプ
	//if (TYPE == ADD)
	//{
	//	CDirectX::Get_pD3DDevice()->SetTextureStageState(NUMBER, D3DTSS_COLORARG1, D3DTA_CURRENT);
	//	CDirectX::Get_pD3DDevice()->SetTextureStageState(NUMBER, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	//	CDirectX::Get_pD3DDevice()->SetTextureStageState(NUMBER, D3DTSS_COLOROP, D3DTOP_ADD);
	//}
}

//***********************************************************************************************************
// 終了
//***********************************************************************************************************
void CTexture_2D_Base::Finalise()
{

	if ( pTexture != NULL )
	{	// テクスチャの解放
		for ( int i = 0 ; i < nUse_Texture_Num ; i++ )
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if ( Tex_2D_Data != NULL )
	{	// テクスチャ情報配列の解放
		delete[] Tex_2D_Data;
		Tex_2D_Data = NULL;
	}

	if ( aVertex != NULL )
	{	// 頂点情報配列の解放
		delete[] aVertex;
		aVertex = NULL;
	}
}

//***********************************************************************************************************
// 更新
//***********************************************************************************************************
void CTexture_2D_Base::Update()
{
	// 頂点情報更新
	//*******************************************************************************************************
	SetVertex();

	// テクスチャ座標情報更新
	//*******************************************************************************************************
	SetTexture();

	// テクスチャカラー情報更新
	//*******************************************************************************************************
	SetColor();
}

//***********************************************************************************************************
// 描画
//***********************************************************************************************************
void CTexture_2D_Base::Draw( int NUMBER, int SET_TEXTURE)
{
	CDirectX::Get_pD3DDevice()->SetFVF(FVF_VERTEX_2D);

	// テクスチャのセット
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetTexture( 0, pTexture[SET_TEXTURE] );

	// アルファテストの有効化
	//***************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);


	// ポリゴンの描画
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(	D3DPT_TRIANGLESTRIP,			// プリミティブの種類
													NUM_POLYGON,					// ポリゴン数
													&aVertex[NUMBER * NUM_VERTEX],	// 配列の先頭アドレス
													sizeof(VERTEX_2D) );			// 頂点のデータの大きさ

	// 加算合成設定を元に戻す
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// アルファテストの有効化設定を元に戻す
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

}


//***********************************************************************************************************
// 頂点情報初期化
//***********************************************************************************************************
void CTexture_2D_Base::MakeVertex()
{
	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 頂点座標の設定
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx =
		aVertex[i * NUM_VERTEX + 1].vtx =
		aVertex[i * NUM_VERTEX + 2].vtx =
		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3();


		// rhwの設定(1.0固定)
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].rhw =
		aVertex[i * NUM_VERTEX + 1].rhw =
		aVertex[i * NUM_VERTEX + 2].rhw =
		aVertex[i * NUM_VERTEX + 3].rhw = 1.0f;

		// 頂点カラーの設定(0～255)
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

		// テクスチャ座標
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2( 0.0f, 0.0f );

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2( 1.0f, 0.0f );

		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2( 0.0f, 1.0f );

		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}
}

//↓↓↓↓ テクスチャ情報更新関数( Private ) ↓↓↓↓

//***********************************************************************************************************
//　頂点情報更新
//***********************************************************************************************************
void CTexture_2D_Base::SetVertex()
{
	//float Rotate;

	// 頂点座標の設定
	//*******************************************************************************************************
	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );

		aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );

		aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );

		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );
	}
}

//***********************************************************************************************************
//　テクスチャ座標情報更新
//***********************************************************************************************************
void CTexture_2D_Base::SetTexture()
{
	for (int i = 0; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x,
														Tex_2D_Data[i].Tex_Pos.y );

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x + Tex_2D_Data[i].Tex_Anim.x,
														Tex_2D_Data[i].Tex_Pos.y );

		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x,
														Tex_2D_Data[i].Tex_Pos.y + Tex_2D_Data[i].Tex_Anim.y );

		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x + Tex_2D_Data[i].Tex_Anim.x,
														Tex_2D_Data[i].Tex_Pos.y + Tex_2D_Data[i].Tex_Anim.y );
	}
}

//***********************************************************************************************************
//　テクスチャカラー情報更新
//***********************************************************************************************************
void CTexture_2D_Base::SetColor()
{
	for ( int i = 0; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA( Tex_2D_Data[i].Red, 
														 Tex_2D_Data[i].Green, 
														 Tex_2D_Data[i].Brue, 
														 Tex_2D_Data[i].Alpha );
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************