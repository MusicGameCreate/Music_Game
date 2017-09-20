//***********************************************************************************************************
//
// DirectX環境設定( 2D,3D環境 )
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CDirectX.h"


//***********************************************************************************************************
// 静的変数定義
//***********************************************************************************************************
LPDIRECT3D9			CDirectX::pD3D			= NULL;
LPDIRECT3DDEVICE9	CDirectX::pD3DDevice	= NULL;

//***********************************************************************************************************
// 初期化処理
// bWindow   :ウインドウモードにするかどうか
//***********************************************************************************************************
HRESULT CDirectX::Init( HWND hWnd , bool bWindow )
{
	D3DPRESENT_PARAMETERS		d3dpp;
	D3DDISPLAYMODE				d3ddm;

	//Direct3Dオブジェクトの生成
	//*******************************************************************************************************
	if( ( pD3D = Direct3DCreate9(D3D_SDK_VERSION) ) == NULL )
		return E_FAIL;

	//現在のディスプレイモードを取得
	//*******************************************************************************************************
	if( FAILED( pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return E_FAIL;


	//デバイスのプレゼンテーションパラメータの設定
	//*******************************************************************************************************
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//ワームをゼロクリア
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= d3ddm.Format;				//カラーモードの指定
	d3dpp.BackBufferCount			= 1;						//バックバッファの数
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	//映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					//ウインドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						//デプスバッファ(Zバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				//デプスバッファとして16bitを使う

	if( bWindow )
	{
		//ウインドウモード
		d3dpp.FullScreen_RefreshRateInHz	= 0;								//リフレッシュレート(指定できないので0固定)
		d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;	//インターバル(VSyncを待たずに描画)
	}
	else
	{
		//フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;			//リフレッシュレート(現在の速度に合わせる)
		d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;		//インターバル(VSyncを待って描画)
	}

	//デバイスオブジェクトの生成
	//[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行う
	if ( FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,						//ディスプレイアダプタ
									D3DDEVTYPE_HAL,							//デバイスタイプ
									hWnd,									//フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	//デバイス作成制御の組み合わせ
									&d3dpp,									//デバイスのプレゼンテーションパラメータ
									&pD3DDevice)))							//デバイスインターフェースへのポインタ
	{
		//上記の設定が失敗したら
		//[デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行う
		if ( FAILED( pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&pD3DDevice)))
		{

			//上記の設定が失敗したら
			//[デバイス作成制御]<描画>と<頂点処理>をCPUで行う
			if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&pD3DDevice)))
			{
				//初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートパラメータの設定
	//***********************************

	//裏面をカリング
	pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	//アルファブレンドを行う
	pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	//ソースの設定
	pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//デストの設定
	pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	//
	pD3DDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );
	
	// テクスチャステートパラメータの設定
	//**************************************

	// アルファブレンディング処理を設定
	//**************************************
	

	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1,   D3DTA_TEXTURE );	// テクスチャ
																				// ×
	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2,   D3DTA_DIFFUSE );	// ディフューズ
	pD3DDevice->SetTextureStageState( 0,   D3DTSS_COLOROP, D3DTOP_MODULATE);	// テクスチャとディフューズを乗算合成して出力
	

	pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1,   D3DTA_TEXTURE );	// テクスチャ
																				// ×
	pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2,   D3DTA_DIFFUSE );	// ディフューズ
	pD3DDevice->SetTextureStageState( 0,   D3DTSS_ALPHAOP, D3DTOP_MODULATE );	// テクスチャとディフューズを乗算合成して出力

	//サンプラーステートパラメータの設定
	//**************************************

	//テクスチャU値の繰り返し設定
	pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );

	//テクスチャV値の繰り返し設定
	pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

	//テクスチャ拡大時の補間設定
	pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	//テクスチャ縮小時の補間設定
	pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	pD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

	// ライトを有効にする
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// アンビエントライト（環境光）を設定する
	pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	// スペキュラ（鏡面反射）を有効にする
	pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);


	return S_OK;
}

//***********************************************************************************************************
// 描画開始
//***********************************************************************************************************
bool CDirectX::Render_Begin()
{
	//バックバッファ＆Ｚバッファのクリア
	pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3Dによる描画の開始
	return SUCCEEDED( pD3DDevice->BeginScene() );
}

//***********************************************************************************************************
// 描画終了
//***********************************************************************************************************
void CDirectX::Render_End()
{
	//Direct3Dによる描画の終了
	pD3DDevice->EndScene();

	//バックバッファとフロントバッファの入れ替え
	//pSourceRect			:転送元矩形
	//pDestRect				:転送元矩形
	//hDestWindowOverride	:転送元ウインドウへのポインタ
	//pDirtyRegion			:通常はNULLで
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//***********************************************************************************************************
// 終了処理
//***********************************************************************************************************
void CDirectX::Finalise()
{
	if ( pD3DDevice != NULL )
	{	//デバイスの開放
		pD3DDevice->Release();
		pD3DDevice = NULL;
	}

	if ( pD3D != NULL )
	{	//Direct3Dオブジェクトの開放
		pD3D->Release();
		pD3D = NULL;
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************