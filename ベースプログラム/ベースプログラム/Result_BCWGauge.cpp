//*************************************************************************
//
// リザルト画面・ボタン・クリック・ホイールノーツ成功割合バー
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "Result_BCWGauge.h"
#include "DirectX_Library.h"

// 1％ = 2.83f

//*************************************************************************
// コンストラクタ
//*************************************************************************
Result_BCWGauge::Result_BCWGauge(void)
{	
	{// プレイした曲の各ノーツの総数を取得
		// ボタンノーツ総数を格納
		nMax_ButtonNort = 0;

		// クリックノーツ総数を格納
		nMax_ClickNort = 0;

		// ホイールノーツ総数を格納
		nMax_WheelNort = 0;
	}


	// ボタン・クリック・ホイールノーツの成功割合(％)を格納
	//*********************************************************************
	nButtonGauge	= 50;
	nClickGauge		= 25;
	nWheelGauge		= 25;



	// とりあえずNULLに
	//*********************************************************************
	pTexture		= NULL;	// テクスチャ画像情報
	aVertex			= NULL; // 頂点情報配列


	// ゲージを3つ生成
	//*********************************************************************
	nObject_Num = 3;

	// 使用テクスチャ分サイズを確保
	//*********************************************************************
	pTexture = new LPDIRECT3DTEXTURE9[nObject_Num];

	// オブジェクトの個数分、必要なサイズを確保
	// 頂点数 * 個数分 = 必要なオブジェクト分の頂点数(前から4個ずつ使用)
	//*********************************************************************
	aVertex = new VERTEX_2D[NUM_VERTEX * nObject_Num];

	// 各種情報初期化
	//*********************************************************************
	for (int i = 0; i < nObject_Num; i++)
	{
		// 頂点座標
		//*****************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx = 
		aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(788.0f, 556.0f + i * 26.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].vtx = 
		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(788.0f, 576.0f + i * 26.0f, 0.0f);

		// rhwの設定(1.0固定)
		//******************************************************************
		aVertex[i * NUM_VERTEX + 0].rhw =
		aVertex[i * NUM_VERTEX + 1].rhw =
		aVertex[i * NUM_VERTEX + 2].rhw =
		aVertex[i * NUM_VERTEX + 3].rhw = 1.0f;

		// 頂点カラーの設定(0～255)
		//******************************************************************
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標
		//******************************************************************
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// テクスチャの作成
	//*********************************************************************
	CREATE_TEXTURE( pTexture[0], 0xffff00ff );
	CREATE_TEXTURE( pTexture[1], 0xffffff00 );
	CREATE_TEXTURE( pTexture[2], 0xff00ff70 );

	float fAdd_Length = 0.0f;

	{// ボタンゲージの長さを割合に応じて変更
		fAdd_Length = (float)(nButtonGauge * 2.83f);

		if (fAdd_Length > 283.0f)
			fAdd_Length = 283.0f;

		aVertex[0 * NUM_VERTEX + 1].vtx.x += fAdd_Length;
		aVertex[0 * NUM_VERTEX + 3].vtx.x += fAdd_Length;
	}


	{// クリックゲージの長さを割合に応じて変更
		fAdd_Length = (float)(nClickGauge * 2.83f);

		if (fAdd_Length > 283.0f)
			fAdd_Length = 283.0f;

		aVertex[1 * NUM_VERTEX + 1].vtx.x += fAdd_Length;
		aVertex[1 * NUM_VERTEX + 3].vtx.x += fAdd_Length;
	}


	{// ホイールゲージの長さを割合に応じて変更
		fAdd_Length = (float)(nWheelGauge * 2.83f);

		if (fAdd_Length > 283.0f)
			fAdd_Length = 283.0f;

		aVertex[2 * NUM_VERTEX + 1].vtx.x += fAdd_Length;
		aVertex[2 * NUM_VERTEX + 3].vtx.x += fAdd_Length;
	}

}

//*************************************************************************
// デストラクタ
//*************************************************************************
Result_BCWGauge::~Result_BCWGauge(void)
{
	if (pTexture != NULL)
	{	// テクスチャの解放
		for (int i = 0; i < nObject_Num; i++)
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if (aVertex != NULL)
	{	// 頂点情報配列の解放
		delete[] aVertex;
		aVertex = NULL;
	}
}

//*************************************************************************
// 更新処理
//*************************************************************************
void Result_BCWGauge::Update(void)
{

}

//*************************************************************************
// 描画処理
//*************************************************************************
void Result_BCWGauge::Draw(void)
{
	CDirectX::Get_pD3DDevice()->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < nObject_Num; i++)
	{
		// テクスチャのセット
		//*****************************************************************
		CDirectX::Get_pD3DDevice()->SetTexture(0, pTexture[i]);

		// ポリゴンの描画
		//*****************************************************************
		CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
													NUM_POLYGON,				// ポリゴン数
													&aVertex[i * NUM_VERTEX],	// 配列の先頭アドレス
													sizeof(VERTEX_2D));			// 頂点のデータの大きさ
	}
}

//*************************************************************************
// EOF
//*************************************************************************
