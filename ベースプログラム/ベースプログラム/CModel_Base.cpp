//***********************************************************************************************************
//
// モデル描画基本クラス
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CModel_Base.h"

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
CModel_Base::CModel_Base()
{
	// とりあえずNULLに
	//*******************************************************************************************************
	pD3DXMesh		= NULL;
	pD3DXBuffMat	= NULL;
	pD3DXMat		= NULL;
	pTexture		= NULL;
	pMaterial		= NULL;
	Model_Data		= NULL;

	// マテリアル数は最初は0に
	//*******************************************************************************************************
	nNumMat = 0;
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
CModel_Base::~CModel_Base()
{

}

//***********************************************************************************************************
// 初期化処理
//***********************************************************************************************************
void CModel_Base::Init( char* X_FILE )
{

	// Xファイル読み込み、必要な情報を取得
	//*******************************************************************************************************
	D3DXLoadMeshFromX(	X_FILE,						// 使用するXファイル名
						D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
						CDirectX::Get_pD3DDevice(),	// デバイスのポインタ
						NULL,						// 隣接性データを含むバッファへのポインタ
						&pD3DXBuffMat,				// マテリアルデータを含むバッファ
						NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
						&nNumMat,					// D3DXMATERIAL構造体の数
						&pD3DXMesh );				// メッシュのポインタ
					
	// テクスチャ読み込み
	//*******************************************************************************************************
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXBuffMat->GetBufferPointer();

	pMaterial	= new D3DMATERIAL9[nNumMat];
	pTexture	= new LPDIRECT3DTEXTURE9[nNumMat];

	for ( DWORD i = 0; i < nNumMat; i ++ )
	{
		pMaterial[i]		= pD3DMaterials[i].MatD3D;
		pMaterial[i].Ambient= pMaterial[i].Diffuse;
		pTexture[i]			= NULL;

		if ( pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0] )
		{
			// テクスチャファイルを読み込む
			//***********************************************************************************************
			D3DXCreateTextureFromFileA(	CDirectX::Get_pD3DDevice(),
										pD3DMaterials[i].pTextureFilename,
										&pTexture[i]);
		}
	}
}

//***********************************************************************************************************
// 終了処理
//***********************************************************************************************************
void CModel_Base::Finalise()
{
	if ( pD3DXMesh != NULL )
	{	// メッシュ解放
		pD3DXMesh->Release();
		pD3DXMesh = NULL;
	}
	if ( pD3DXBuffMat != NULL )
	{	// マテリアル開放
		pD3DXBuffMat->Release();
		pD3DXBuffMat = NULL;
	}
	
	//if ( pTexture != NULL )
	//{	// テクスチャ解放
	//	for ( DWORD i = 0; i < nNumMat; i++ )
	//	{
	//		pTexture[i]->Release();
	//	}

	//	delete[] pTexture;
	//	pTexture = NULL;
	//}	

	if ( pMaterial != NULL )
	{
		delete[] pMaterial;
		pMaterial = NULL;
	}

	if ( Model_Data != NULL )
	{	// モデル情報構造体解放
		delete[] Model_Data;
		Model_Data = NULL;
	}
}

//***********************************************************************************************************
// 更新処理
//***********************************************************************************************************
void CModel_Base::Update()
{
	for (int i = 0; i < nObject_Num; i++)
	{
		// ワールドマトリクスの初期化
		//***************************************************************************************************
		D3DXMatrixIdentity(&Model_Data[i].World_Matrix);

		// 拡大率をモデルに反映
		//***************************************************************************************************
		D3DXMatrixScaling( &Model_Data[i].Scale_Matrix, Model_Data[i].Model_Scale.x, Model_Data[i].Model_Scale.y, Model_Data[i].Model_Scale.z);
		D3DXMatrixMultiply(	&Model_Data[i].World_Matrix, &Model_Data[i].World_Matrix, &Model_Data[i].Scale_Matrix);


		// 回転角度をモデルに反映
		//***************************************************************************************************
		D3DXMatrixRotationYawPitchRoll(	&Model_Data[i].Rotate_Matrix, Model_Data[i].Model_Rot.y, Model_Data[i].Model_Rot.x, Model_Data[i].Model_Rot.z);
		D3DXMatrixMultiply(	&Model_Data[i].World_Matrix, &Model_Data[i].World_Matrix, &Model_Data[i].Rotate_Matrix);			


		// 座標をモデルに反映
		//***************************************************************************************************
		D3DXMatrixTranslation( &Model_Data[i].Trans_Matrix, Model_Data[i].Model_Pos.x, Model_Data[i].Model_Pos.y, Model_Data[i].Model_Pos.z);
		D3DXMatrixMultiply(	&Model_Data[i].World_Matrix, &Model_Data[i].World_Matrix, &Model_Data[i].Trans_Matrix );

	}
}

//***********************************************************************************************************
// 描画処理
//***********************************************************************************************************
void CModel_Base::Draw()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ワールドマトリクスの設定
		//***************************************************************************************************
		CDirectX::Get_pD3DDevice()->SetTransform( D3DTS_WORLD, &Model_Data[i].World_Matrix );

		for ( int i = 0; i < (int)nNumMat; i ++ )
		{
			// マテリアルの設定
			//***********************************************************************************************
			CDirectX::Get_pD3DDevice()->SetMaterial( &pMaterial[i] );

			// テクスチャの設定
			//***********************************************************************************************
			if ( bUse_Texture == true )
				CDirectX::Get_pD3DDevice()->SetTexture( 0, pTexture[i] );
			if ( bUse_Texture == false )
				CDirectX::Get_pD3DDevice()->SetTexture( 0, NULL );

			// 描画
			//***********************************************************************************************
			pD3DXMesh->DrawSubset(i);
		}
	}

	// 加算合成設定を元に戻す
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************