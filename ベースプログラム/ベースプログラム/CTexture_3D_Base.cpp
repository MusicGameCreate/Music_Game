//***********************************************************************************************************
//
// 3D環境での画像描画基本クラス
//
//***********************************************************************************************************


//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CTexture_3D_Base.h"


//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
CTexture_3D_Base::CTexture_3D_Base()
{
	// とりあえずNULLに
	//*******************************************************************************************************
	pTexture	= NULL;		// テクスチャ情報の初期化
	Tex_3D_Data = NULL;		// テクスチャ情報配列
	aVertex		= NULL;		// 頂点情報配列

	// オブジェクト数は最初は1に設定
	//*******************************************************************************************************
	nObject_Num	= 1;

	// テクスチャ数は最初は1に設定
	//*******************************************************************************************************
	nUse_Texture_Num = 1;

	// 各種設定は最初は無適用
	//*******************************************************************************************************
	bBillboard	= false;	// ビルボード指定
	bAlphaTest	= false;	// αテスト適用指定
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
CTexture_3D_Base::~CTexture_3D_Base()
{

}

//***********************************************************************************************************
// 初期化
//***********************************************************************************************************
void CTexture_3D_Base::Init()
{
	// オブジェクトの個数分、必要なサイズを確保
	// 頂点数 * 個数分 = 必要なオブジェクト分の頂点数(前から4個ずつ使用)
	//*******************************************************************************************************
	aVertex = new VERTEX_3D[NUM_VERTEX * nObject_Num];

	// 使用テクスチャ分サイズを確保
	//*******************************************************************************************************
	pTexture = new LPDIRECT3DTEXTURE9[nUse_Texture_Num];

	// 頂点情報初期化
	//*******************************************************************************************************
	MakeVertex();
}

//***********************************************************************************************************
// テクスチャ読み込み
//***********************************************************************************************************
void CTexture_3D_Base::Load_Texture(char* TEXTURE_FILE, int NUMBER)
{
	// テクスチャの読み込み
	//*******************************************************************************************************
	D3DXCreateTextureFromFile(	CDirectX::Get_pD3DDevice(),	// デバイスへのポインタ
								TEXTURE_FILE,				// ファイルの名前
								&pTexture[NUMBER]);			// 読み込むメモリー

}

//***********************************************************************************************************
// 終了
//***********************************************************************************************************
void CTexture_3D_Base::Finalise()
{
	if (pTexture != NULL)
	{	// テクスチャの解放
		for (int i = 0; i < nUse_Texture_Num; i++)
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if( Tex_3D_Data != NULL )
	{	// テクスチャ情報配列の解放
		delete[] Tex_3D_Data;
		Tex_3D_Data = NULL;
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
void CTexture_3D_Base::Update()
{
	// 頂点情報更新
	//*******************************************************************************************************
	SetVertex();

	// テクスチャ座標更新
	//*******************************************************************************************************
	SetTexture();

	// カラー情報更新
	//*******************************************************************************************************
	SetColor();
}

//***********************************************************************************************************
// 描画
//***********************************************************************************************************
void CTexture_3D_Base::Draw(int NUMBER, int SET_TEXTURE)
{
	D3DCAPS9 Caps;

	// ライティングを無効にする
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 頂点フォーマットの設定
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetTexture(0, pTexture[SET_TEXTURE]);

	// デバイス機能を取得
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->GetDeviceCaps(&Caps);

	if ( bAlphaTest && Caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
	{
		// アルファテストの有効化
		//***************************************************************************************************
		CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		//CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

		// 不透明にする値の設定
		//***************************************************************************************************
		CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAREF, 0x66);
	}


	// ワールドマトリックスの設定
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetTransform( D3DTS_WORLD, &Tex_3D_Data[NUMBER].mtxWorld );


	// ポリゴンの描画
	//*******************************************************************************************************
		CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(	D3DPT_TRIANGLESTRIP,			// プリミティブの種類
														NUM_POLYGON,					// ポリゴン数
														&aVertex[NUMBER * NUM_VERTEX],	// 配列の先頭アドレス
														sizeof(VERTEX_3D));				// 頂点のデータの大きさ


	// 加算合成設定を元に戻す
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// ライティングを有効にする
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	// アルファテストの無効化
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//***********************************************************************************************************
// 頂点情報初期化
//***********************************************************************************************************
void CTexture_3D_Base::MakeVertex()
{
	for ( int i = 0 ; i < nObject_Num ; i++ )
	{
		// 頂点座標の設定
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx		=
		aVertex[i * NUM_VERTEX + 1].vtx		=
		aVertex[i * NUM_VERTEX + 2].vtx		=
		aVertex[i * NUM_VERTEX + 3].vtx		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		if ( bBillboard == true )
		{
			// 法線の設定( 0.0f, 0.0f, -1.0f 固定)
			//***********************************************************************************************
			aVertex[i * NUM_VERTEX + 0].normal =
			aVertex[i * NUM_VERTEX + 1].normal =
			aVertex[i * NUM_VERTEX + 2].normal =
			aVertex[i * NUM_VERTEX + 3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
		else
		{
			// 法線の設定( 0.0f, 1.0f, 0.0f 固定 )
			//***********************************************************************************************
			aVertex[i * NUM_VERTEX + 0].normal =
			aVertex[i * NUM_VERTEX + 1].normal =
			aVertex[i * NUM_VERTEX + 2].normal =
			aVertex[i * NUM_VERTEX + 3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		

		// 頂点カラーの設定(0～255)
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].diffuse =
		aVertex[i * NUM_VERTEX + 1].diffuse =
		aVertex[i * NUM_VERTEX + 2].diffuse =
		aVertex[i * NUM_VERTEX + 3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].tex		= D3DXVECTOR2(0.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 1].tex		= D3DXVECTOR2(1.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].tex		= D3DXVECTOR2(0.0f, 1.0f);
		aVertex[i * NUM_VERTEX + 3].tex		= D3DXVECTOR2(1.0f, 1.0f);
	}

}

//***********************************************************************************************************
// 頂点座標更新
//***********************************************************************************************************
void CTexture_3D_Base::SetVertex()
{
	// ビューマトリックスを取得
	//*******************************************************************************************************
	mtxView = CCamera::GetMtxView();

	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		if ( bBillboard == true )
		{
			aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2,
															Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);

			aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2,
															Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);

			aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2,
															-Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);

			aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2,
															-Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);
		}
		else
		{
			//aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												Tex_3D_Data[i].Obj_Size.y / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			//aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												Tex_3D_Data[i].Obj_Size.y / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			//aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												-Tex_3D_Data[i].Obj_Size.y / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			//aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												-Tex_3D_Data[i].Obj_Size.y / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(-Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				Tex_3D_Data[i].Obj_Size.y / 2);

			aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				Tex_3D_Data[i].Obj_Size.y / 2);

			aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(-Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				-Tex_3D_Data[i].Obj_Size.y / 2);

			aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				-Tex_3D_Data[i].Obj_Size.y / 2);
		}

		// ワールドマトリックスの初期化
		//***************************************************************************************************
		D3DXMatrixIdentity( &Tex_3D_Data[i].mtxWorld );

		if ( bBillboard == true )
		{
			// ポリゴンを正面に向ける
#if 1
			// 逆行列を求める
			//***********************************************************************************************
			D3DXMatrixInverse( &Tex_3D_Data[i].mtxWorld, NULL, &mtxView );

			Tex_3D_Data[i].mtxWorld._41 = 0.0f;
			Tex_3D_Data[i].mtxWorld._42 = 0.0f;
			Tex_3D_Data[i].mtxWorld._43 = 0.0f;
			//平行移動成分をなくす

			// 転置行列を求める
			//***********************************************************************************************
			Tex_3D_Data[i].mtxWorld._11 = mtxView._11;
			Tex_3D_Data[i].mtxWorld._12 = mtxView._21;
			Tex_3D_Data[i].mtxWorld._13 = mtxView._31;
			Tex_3D_Data[i].mtxWorld._14 = 0.0f;
			Tex_3D_Data[i].mtxWorld._21 = mtxView._12;
			Tex_3D_Data[i].mtxWorld._22 = mtxView._22;
			Tex_3D_Data[i].mtxWorld._23 = mtxView._32;
			Tex_3D_Data[i].mtxWorld._24 = 0.0f;
			Tex_3D_Data[i].mtxWorld._31 = mtxView._13;
			Tex_3D_Data[i].mtxWorld._32 = mtxView._23;
			Tex_3D_Data[i].mtxWorld._33 = mtxView._33;
			Tex_3D_Data[i].mtxWorld._34 = 0.0f;
			Tex_3D_Data[i].mtxWorld._41 = 0.0f;
			Tex_3D_Data[i].mtxWorld._42 = 0.0f;
			Tex_3D_Data[i].mtxWorld._43 = 0.0f;
			Tex_3D_Data[i].mtxWorld._44 = 1.0f;

#else
			// 逆行列を求める
			D3DXMatrixInverse(&Tex_3D_Data[i].mtxWorld,
				NULL,
				&mtxView);

			Tex_3D_Data[i].mtxWorld._41 = 0.0f;
			Tex_3D_Data[i].mtxWorld._42 = 0.0f;
			Tex_3D_Data[i].mtxWorld._43 = 0.0f;
#endif
		}

		// スケールを反映
		//***************************************************************************************************
		D3DXMatrixScaling( &Tex_3D_Data[i].mtxScale, Tex_3D_Data[i].Obj_Scale.x, Tex_3D_Data[i].Obj_Scale.y, Tex_3D_Data[i].Obj_Scale.z);
		D3DXMatrixMultiply(	&Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxScale);


		// 回転角度を反映
		//***************************************************************************************************
		D3DXMatrixRotationYawPitchRoll(&Tex_3D_Data[i].mtxRot, Tex_3D_Data[i].Obj_Rot.y, Tex_3D_Data[i].Obj_Rot.x, Tex_3D_Data[i].Obj_Rot.z);
		D3DXMatrixMultiply(&Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxRot);

		// 移動を反映
		//***************************************************************************************************
		D3DXMatrixTranslation(	&Tex_3D_Data[i].mtxTranslate, Tex_3D_Data[i].Obj_Pos.x, Tex_3D_Data[i].Obj_Pos.y, Tex_3D_Data[i].Obj_Pos.z);
		D3DXMatrixMultiply( &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxTranslate );
	}
}

//***********************************************************************************************************
// テクスチャ座標更新
//***********************************************************************************************************
void CTexture_3D_Base::SetTexture()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x,
														Tex_3D_Data[i].Tex_Pos.y);

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x + Tex_3D_Data[i].Tex_Anim.x,
														Tex_3D_Data[i].Tex_Pos.y);

		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x,
														Tex_3D_Data[i].Tex_Pos.y + Tex_3D_Data[i].Tex_Anim.y);

		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x + Tex_3D_Data[i].Tex_Anim.x,
														Tex_3D_Data[i].Tex_Pos.y + Tex_3D_Data[i].Tex_Anim.y);
	}
}

//***********************************************************************************************************
// テクスチャカラー情報更新
//***********************************************************************************************************
void CTexture_3D_Base::SetColor()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].diffuse =
		aVertex[i * NUM_VERTEX + 1].diffuse =
		aVertex[i * NUM_VERTEX + 2].diffuse =
		aVertex[i * NUM_VERTEX + 3].diffuse = D3DCOLOR_RGBA( Tex_3D_Data[i].Red, 
															 Tex_3D_Data[i].Green, 
															 Tex_3D_Data[i].Brue, 
															 Tex_3D_Data[i].Alpha );
	}
}

void CTexture_3D_Base::QuaternionRotate()
{
	q.x = q.y = q.z = NAxis.x = NAxis.y = 0.0f;
	q.w = NAxis.z = 1.0f;

	//何もしない行列を作る
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&TurnMat);

	// 画像の左端が原点になるように平行移動
	D3DXMatrixTranslation(&mat, Tex_3D_Data[0].Obj_Size.x / 2, 0.0f, 0.0f);

}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************